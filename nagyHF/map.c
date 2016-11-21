#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "window.h"

void map_create(map* m, size_t w, size_t h)
{
	size_t i;
	m->width = w;
	m->height = h;
	m->grid = (TileID**)malloc(sizeof(TileID*) * w);
	for (i = 0; i < w; i++)
	{
		m->grid[i] = (TileID*)malloc(sizeof(TileID) * h);
		memset(m->grid[i], T_Air, h);
	}

	for (i = 0; i < w * h; i++)
	{
		m->grid[i % w][i / h] = i % 3 == 0 ? T_Ground : T_Air;
	}
}

void map_offset_by(map* m, size_t x, size_t y)
{
	int newx = m->xoff + x;
	int newy = m->yoff + y;
	newx = newx < 0 ? 0 : newx;
	newy = newy < 0 ? 0 : newy;
	int maxx = m->width * TILE_SIZE - WIND_W;
	int maxy = m->height * TILE_SIZE - WIND_H;
	maxx = maxx < 0 ? 0 : maxx;
	maxy = maxy < 0 ? 0 : maxy;
	if (newx > maxx) newx = maxx;
	if (newy > maxy) newy = maxy;
	m->xoff = newx;
	m->yoff = newy;
}

void map_render(map* m, SDL_Renderer* renderer)
{
	size_t xp = m->xoff / TILE_SIZE;
	size_t yp = m->yoff / TILE_SIZE;
	size_t offx = m->xoff % TILE_SIZE;
	size_t offy = m->yoff % TILE_SIZE;
	size_t xl = WIND_W / TILE_SIZE + 1;
	size_t yl = WIND_H / TILE_SIZE + 2;
	size_t x, y;
	size_t xa, ya;
	TileID tid;
	for (y = 0; y < yl; y++)
	{
		ya = yp + y;
		if (ya >= m->height) continue;
		for (x = 0; x < xl; x++)
		{
			xa = xp + x;
			if (xa >= m->width) continue;
			tid = m->grid[xa][ya];
			if (tid == T_Air)
			{
				SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0xff, 0xff);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xcc, 0xdd, 0x44, 0xff);
			}
			SDL_Rect rec = { x * TILE_SIZE - offx, y * TILE_SIZE - offy, TILE_SIZE, TILE_SIZE };
			SDL_RenderFillRect(renderer, &rec);
		}
	}
}