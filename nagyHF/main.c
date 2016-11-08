#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <SDL.h>
#include "loader.h"
#include "game_state.h"
#include "menu_state.h"
#include "input.h"

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

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialization error: %s\n", SDL_GetError());
		return 0;
	}

	if (!loader_init())
	{
		return 0;
	}

	if (create_window("Bounce MapEditor", 960, 540))
	{
		running = true;
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
					mouse.current_state = true;
					break;

				case SDL_MOUSEBUTTONUP:
					mouse.current_state = false;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_BACKSPACE:
						keyboard.typed = true;
						keyboard.last_typed = '\r';
						break;
					}

				case SDL_TEXTINPUT:
					if (isprint(event.text.text[0]))
					{
						keyboard.typed = true;
						keyboard.last_typed = event.text.text[0];
					}
					break;
				}
			}
			mouse.released = (mouse.last_state && !mouse.current_state);
			mouse.pressed = (!mouse.last_state && mouse.current_state);
			mouse.last_state = mouse.current_state;

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