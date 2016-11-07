#include <string.h>
#include "fontatlas.h"

void atlas_draw(fontatlas* atlas, size_t x, size_t y, const char* text, SDL_Color col, SDL_Renderer* renderer)
{
	atlas_drawn(atlas, x, y, text, strlen(text), col, renderer);
}

void atlas_drawn(fontatlas* atlas, size_t x, size_t y,
	const char* text, size_t n, SDL_Color col, SDL_Renderer* renderer)
{
	char* at = text;
	SDL_Rect rect = { x, y, 0, 0 };
	while (n--)
	{
		char curr = *at++;
		if (curr == '\n')
		{
			rect.x = x;
			rect.y += atlas->pt;
		}
		else
		{
			size_t idx = (size_t)(strchr(ATLAS_CHARS, curr) - ATLAS_CHARS);
			glyph g = atlas->chars[idx];
			SDL_SetTextureColorMod(g.texture, col.r, col.g, col.b);
			rect.w = g.w;
			rect.h = g.h;
			SDL_RenderCopy(renderer, g.texture, NULL, &rect);
			rect.x += g.w;
		}
	}
}