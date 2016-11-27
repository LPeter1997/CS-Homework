#include <SDL.h>
#include "grid_selector.h"
#include "input.h"

static void grid_button(button* b)
{
	grid_selector* gs = b->userdata;
	size_t xp = mouse.x - gs->x;
	size_t yp = mouse.y - gs->y;
	xp /= (GS_SIZE + GS_OFFSET);
	yp /= (GS_SIZE + GS_OFFSET);

	gs->sel_x = xp;
	gs->sel_y = yp;
	gs->sel_btn = &gs->buttons[xp + yp * gs->width];
}

void grid_selector_create(grid_selector* gs, size_t x, size_t y, size_t w, size_t h)
{
	size_t i;
	size_t j;
	gs->sel_x = 0;
	gs->sel_y = 0;
	gs->x = x;
	gs->y = y;
	gs->width = w;
	gs->height = h;
	gs->buttons = (button*)malloc(sizeof(button) * w * h);
	SDL_Rect rect = { gs->x, gs->y, GS_SIZE, GS_SIZE };
	SDL_Color norm = { 0x22, 0x22, 0x22, 0xff };
	SDL_Color hil = { 0xaa, 0xaa, 0xaa, 0xff };
	SDL_Color press = { 0x11, 0x11, 0x11, 0xff };
	for (j = 0; j < gs->height; j++)
	{
		rect.x = gs->x;
		for (i = 0; i < gs->width; i++)
		{
			button_create(&gs->buttons[i + j * gs->width], rect, norm, hil, press, NULL, grid_button);
			gs->buttons[i + j * gs->width].userdata = gs;
			rect.x += GS_SIZE + GS_OFFSET;
		}
		rect.y += GS_SIZE + GS_OFFSET;
	}
}

void grid_selector_add(grid_selector* gs, size_t w, size_t h, SDL_Texture* tex)
{
	gs->buttons[w + h * gs->width].label = tex;
	SDL_Rect rect = { gs->x + w * (GS_SIZE + GS_OFFSET) + GS_ISIZE / 2,
		gs->y + h * (GS_SIZE + GS_OFFSET) + GS_ISIZE / 2,
		GS_SIZE - GS_ISIZE, GS_SIZE - GS_ISIZE };
	gs->buttons[w + h * gs->width].l_bounds = rect;
}

void grid_selector_update(grid_selector* gs)
{
	size_t i;
	for (i = 0; i < gs->width * gs->height; i++)
	{
		if (gs->buttons[i].label)
			button_update(&gs->buttons[i]);
	}
}

void grid_selector_render(grid_selector* gs, SDL_Renderer* renderer)
{
	size_t i;
	for (i = 0; i < gs->width * gs->height; i++)
	{
		if (gs->buttons[i].label)
			button_render(&gs->buttons[i], renderer);
	}
	// Draw selector geometry
	SDL_SetRenderDrawColor(renderer, 0xbb, 0xbb, 0xbb, 0xff);
	size_t xp = gs->x + gs->sel_x * (GS_SIZE + GS_OFFSET);
	size_t yp = gs->y + gs->sel_y * (GS_SIZE + GS_OFFSET);
	SDL_Rect rect = { xp - GS_STROKE / 2, yp - GS_STROKE / 2, GS_SIZE / 2 + GS_STROKE / 2, GS_STROKE };
	SDL_RenderFillRect(renderer, &rect);
	rect.x += GS_SIZE / 2 + GS_OFFSET / 2;
	rect.y += GS_SIZE;
	SDL_RenderFillRect(renderer, &rect);
	SDL_Rect rect2 = { xp - GS_STROKE / 2, yp - GS_STROKE / 2, GS_STROKE, GS_SIZE / 2 + GS_STROKE / 2 };
	SDL_RenderFillRect(renderer, &rect2);
	rect2.x += GS_SIZE;
	rect2.y += GS_SIZE / 2 + GS_OFFSET / 2;
	SDL_RenderFillRect(renderer, &rect2);
}