#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <SDL.h>
#include "loader.h"
#include "game_state.h"
#include "menu_state.h"
#include "input.h"
#include "window.h"
#undef main

SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;
bool create_window(const char* title, size_t w, size_t h)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("SDL window creation error: %s\n", SDL_GetError());
		return false;
	}

	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("Could not create renderer: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	return true;
}

int main(void)
{
	bool running;
	SDL_Event event;
	size_t i;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialization error: %s\n", SDL_GetError());
		return 0;
	}

	if (!loader_init())
	{
		return 0;
	}

	if (create_window("Bounce MapEditor", WIND_W, WIND_H))
	{
		running = true;
		for (i = 0; i < __MB_Cnt__; i++)
		{
			mouse.buttons[i].current_state = false;
			mouse.buttons[i].last_state = false;
		}
		for (i = 0; i < __KP_Cnt__; i++)
		{
			keyboard.keys[i].current_state = false;
			keyboard.keys[i].last_state = false;
		}

		gsm_push(menu_create(), renderer);

		while (running)
		{
			keyboard.typed = false;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					running = false;
					break;

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouse.x, &mouse.y);
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						mouse.buttons[MB_Left].current_state = true;
					}
					else
					{
						mouse.buttons[MB_Right].current_state = true;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						mouse.buttons[MB_Left].current_state = false;
					}
					else
					{
						mouse.buttons[MB_Right].current_state = false;
					}
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_LEFT:
						keyboard.keys[KP_Left].current_state = true;
						break;

					case SDLK_RIGHT:
						keyboard.keys[KP_Right].current_state = true;
						break;

					case SDLK_UP:
						keyboard.keys[KP_Up].current_state = true;
						break;

					case SDLK_DOWN:
						keyboard.keys[KP_Down].current_state = true;
						break;

					case SDLK_LSHIFT:
					case SDLK_RSHIFT:
						keyboard.keys[KP_Shift].current_state = true;
						break;

					case SDLK_BACKSPACE:
						keyboard.typed = true;
						keyboard.last_typed = '\r';
						break;
					}
					break;

				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_LEFT:
						keyboard.keys[KP_Left].current_state = false;
						break;

					case SDLK_RIGHT:
						keyboard.keys[KP_Right].current_state = false;
						break;

					case SDLK_UP:
						keyboard.keys[KP_Up].current_state = false;
						break;

					case SDLK_DOWN:
						keyboard.keys[KP_Down].current_state = false;
						break;

					case SDLK_LSHIFT:
					case SDLK_RSHIFT:
						keyboard.keys[KP_Shift].current_state = false;
						break;
					}
					break;

				case SDL_TEXTINPUT:
					if (isprint(event.text.text[0]))
					{
						keyboard.typed = true;
						keyboard.last_typed = event.text.text[0];
					}
					break;
				}
			}

			for (i = 0; i < __MB_Cnt__; i++)
			{
				mouse.buttons[i].released = (mouse.buttons[i].last_state && !mouse.buttons[i].current_state);
				mouse.buttons[i].pressed = (!mouse.buttons[i].last_state && mouse.buttons[i].current_state);
				mouse.buttons[i].last_state = mouse.buttons[i].current_state;
			}
			for (i = 0; i < __KP_Cnt__; i++)
			{
				keyboard.keys[i].released = (keyboard.keys[i].last_state && !keyboard.keys[i].current_state);
				keyboard.keys[i].pressed = (!keyboard.keys[i].last_state && keyboard.keys[i].current_state);
				keyboard.keys[i].last_state = keyboard.keys[i].current_state;
			}
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderClear(renderer);

			gsm_update();
			gsm_render(renderer);

			SDL_RenderPresent(renderer);
		}
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	loader_term();
	SDL_Quit();

	return 0;
}
