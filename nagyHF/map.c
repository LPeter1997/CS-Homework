#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "window.h"
#include "mapedit_state.h"

void map_create(map* m, size_t w, size_t h)
{
	size_t i;
	m->width = w;
	m->height = h;
	m->xoff = 0;
	m->yoff = 0;
	m->selx = -1;
	m->sely = -1;
	m->layers_head = (layer*)malloc(sizeof(layer));
	m->current_layer = m->layers_head;
	m->current_layer->prev = NULL;
	m->current_layer->next = NULL;

	m->current_layer->grid = (TileID**)malloc(sizeof(TileID*) * w);
	for (i = 0; i < w; i++)
	{
		m->current_layer->grid[i] = (TileID*)malloc(sizeof(TileID) * h);
		memset(m->current_layer->grid[i], T_Air, h * sizeof(TileID));
	}
}

void map_offset_by(map* m, int x, int y)
{
	int newx = (int)m->xoff + x;
	int newy = (int)m->yoff + y;
	newx = newx < 0 ? 0 : newx;
	newy = newy < 0 ? 0 : newy;
	int maxx = m->width * TILE_SIZE - WIND_W + HUD_WIDTH;
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
	size_t x, y;
	size_t xl = WIND_W / TILE_SIZE + 1;
	size_t yl = WIND_H / TILE_SIZE + 2;
	size_t offx = m->xoff % TILE_SIZE;
	size_t offy = m->yoff % TILE_SIZE;
	layer* lay = m->layers_head;
	// Render bg
	SDL_Rect bgr = { 0, 0, WIND_W - HUD_WIDTH, WIND_H };
	SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xff, 0xff);
	SDL_RenderFillRect(renderer, &bgr);
	while (lay)
	{
		size_t xp = m->xoff / TILE_SIZE;
		size_t yp = m->yoff / TILE_SIZE;
		size_t xa, ya;
		TileID tid;
		size_t alpha = 0x55;
		if (lay == m->current_layer)
		{
			alpha = 0xff;
		}
		for (y = 0; y < yl; y++)
		{
			ya = yp + y;
			if (ya >= m->height) continue;
			for (x = 0; x < xl; x++)
			{
				xa = xp + x;
				if (xa >= m->width) continue;
				tid = lay->grid[xa][ya];
				SDL_Texture* tex = TEX_LOOKUP[tid];
				SDL_Rect rec = { x * TILE_SIZE - offx, y * TILE_SIZE - offy, TILE_SIZE, TILE_SIZE };
				if (tex)
				{
					SDL_SetTextureAlphaMod(tex, alpha);
					SDL_RenderCopy(renderer, tex, NULL, &rec);
					SDL_SetTextureAlphaMod(tex, 0xff);
				}
			}
		}
		lay = lay->next;
	}

	// Draw the grid
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	for (y = 0; y < yl; y++)
	{
		SDL_RenderDrawLine(renderer, 0, y * TILE_SIZE - offy, WIND_W - HUD_WIDTH, y * TILE_SIZE - offy);
	}
	for (x = 0; x < xl; x++)
	{
		SDL_RenderDrawLine(renderer, x * TILE_SIZE - offx, 0, x * TILE_SIZE - offx, WIND_H);
	}

	// Draw selected
	SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
	if (m->selx >= 0 && m->sely >= 0 && m->selx < m->width && m->sely < m->height)
	{
		SDL_Rect rec = { m->selx * TILE_SIZE - offx, m->sely * TILE_SIZE - offy, TILE_SIZE, TILE_SIZE };
		SDL_Rect r1 = { rec.x, rec.y, rec.w, 5 };
		SDL_RenderFillRect(renderer, &r1);
		SDL_Rect r2 = { rec.x, rec.y + rec.h, rec.w, -5 };
		SDL_RenderFillRect(renderer, &r2);
		SDL_Rect r3 = { rec.x, rec.y, 5, rec.h };
		SDL_RenderFillRect(renderer, &r3);
		SDL_Rect r4 = { rec.x + rec.w, rec.y, -5, rec.h };
		SDL_RenderFillRect(renderer, &r4);
	}
}

void map_sel(map* m, int x, int y)
{
	m->selx = (x + m->xoff % TILE_SIZE) / TILE_SIZE;
	m->sely = (y + m->yoff % TILE_SIZE) / TILE_SIZE;
}

void map_plot(map* m, TileID t)
{
	size_t SX = m->selx + (m->xoff / TILE_SIZE);
	size_t SY = m->sely + (m->yoff / TILE_SIZE);
	if (SX >= 0 && SY >= 0 && SX < m->width && SY < m->height)
	{
		m->current_layer->grid[SX][SY] = t;
	}
}

void map_add_layer(map* m)
{
	size_t i;
	layer* tmp = m->current_layer->next;
	m->current_layer->next = (TileID**)malloc(sizeof(TileID*) * m->width);
	m->current_layer->next->grid = (TileID**)malloc(sizeof(TileID*) * m->width);
	for (i = 0; i < m->width; i++)
	{
		m->current_layer->next->grid[i] = (TileID*)malloc(sizeof(TileID) * m->height);
		memset(m->current_layer->next->grid[i], T_Air, m->height * sizeof(TileID));
	}
	m->current_layer->next->prev = m->current_layer;
	m->current_layer = m->current_layer->next;
	m->current_layer->next = tmp;
	if (tmp)
	{
		tmp->prev = m->current_layer;
	}
}