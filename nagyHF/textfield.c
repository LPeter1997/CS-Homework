#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "textfield.h"
#include "input.h"

static uint32_t cur_tick;

void textfield_create(textfield* tf, size_t x, size_t y, fontatlas* fnt, size_t sz, validator val)
{
	string_new(&tf->buffer, sz);
	tf->font = fnt;
	SDL_Rect rec = { x, y, (fnt->pt * sz) * 2 / 3 + 20, sz + 30 };
	tf->bounds = rec;
	tf->active = false;
	tf->valid = val;
}

void textfield_del(textfield* tf)
{
	string_del(&tf->buffer);
}

void textfield_draw(textfield* tf, SDL_Renderer* renderer)
{
	fontatlas* fa = tf->font;
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderFillRect(renderer, &tf->bounds);
	SDL_Color col = { 0x0, 0x0, 0x0, 0xff };
	atlas_draw(fa, tf->bounds.x + 10, tf->bounds.y + 2, tf->buffer.data, col, renderer);
	uint32_t rem = cur_tick % 1000;
	if (rem < 500 && tf->active)
	{
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderDrawLine(renderer, 
			tf->bounds.x + fa->w + 15, tf->bounds.y + 5, 
			tf->bounds.x + fa->w + 15, tf->bounds.y + tf->bounds.h - 5);
	}
}

void textfield_update(textfield* tf)
{
	if (tf->active)
	{
		cur_tick = SDL_GetTicks();
		if (keyboard.typed)
		{
			switch (keyboard.last_typed)
			{
			case '\r':
				if (tf->buffer.len > 0)
				{
					string_remc(&tf->buffer, tf->buffer.len - 1);
				}
				break;

			default:
				if (tf->buffer.len < tf->buffer.reserved - 1 && tf->valid(keyboard.last_typed))
				{
					string_addc(&tf->buffer, keyboard.last_typed);
				}
			}
		}
	}

	if (mouse.buttons[MB_Left].pressed)
	{
		size_t mx = mouse.x;
		size_t my = mouse.y;
		size_t x1 = tf->bounds.x;
		size_t y1 = tf->bounds.y;
		size_t x2 = x1 + tf->bounds.w;
		size_t y2 = y1 + tf->bounds.h;
		tf->active = (mx >= x1 && my >= y1 && mx < x2 && my < y2);
	}
}

void textfield_activate(textfield* tf)
{
	SDL_StartTextInput();
	tf->active = true;
}

void textfield_deactivate(textfield* tf)
{
	tf->active = false;
	SDL_StopTextInput();
}