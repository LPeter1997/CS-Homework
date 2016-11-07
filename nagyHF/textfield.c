#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "textfield.h"
#include "input.h"

static uint32_t cur_tick;

void textfield_create(textfield* tf, size_t x, size_t y, fontatlas* fnt, size_t sz)
{
	string_new(&tf->buffer, sz);
	tf->font = fnt;
	SDL_Rect rec = { x, y, fnt->pt * sz + 20, sz + 20 };
	tf->bounds = rec;
	tf->active = false;
}

void textfield_del(textfield* tf)
{
	string_del(&tf->buffer);
}

void textfield_draw(textfield* tf, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderFillRect(renderer, &tf->bounds);
	SDL_Color col = { 0x0, 0x0, 0x0, 0xff };
	atlas_draw(tf->font, tf->bounds.x + 10, tf->bounds.y, tf->buffer.data, col, renderer);
	uint32_t rem = cur_tick % 2000;
	// TODO: this is hack, does not work!
	if (rem < 1000)
	{
		if (tf->buffer.len > 0)
		{
			if (tf->buffer.data[tf->buffer.len - 1] != '|')
			{
				string_addc(&tf->buffer, '|');
			}
		}
		else
		{
			string_addc(&tf->buffer, '|');
		}
	}
	else
	{
		if (tf->buffer.len > 0)
		{
			if (tf->buffer.data[tf->buffer.len - 1] == '|')
			{
				string_remc(&tf->buffer, tf->buffer.len - 1);
			}
		}
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
				string_addc(&tf->buffer, keyboard.last_typed);
			}
		}
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