#include "button.h"
#include "input.h"

void button_create(button* b, SDL_Rect sz, SDL_Color norm, SDL_Color hil, SDL_Color pr,
	SDL_Texture* lb, callback cb)
{
	b->bounds = sz;
	b->normal_color = norm;
	b->hilight_color = hil;
	b->pressed_color = pr;
	b->label = lb;
	b->action = cb;
	b->active = false;
	b->clicked = false;
	b->blocked = false;
}

void button_render(button* b, SDL_Renderer* renderer)
{
	SDL_Color col;
	if (b->blocked)
	{
		SDL_Color grey = { 0xaa, 0xaa, 0xaa, 0xff };
		col = grey;
	}
	else if (b->active)
	{
		if (b->clicked)
		{
			col = b->pressed_color;
		}
		else
		{
			col = b->hilight_color;
		}
	}
	else
	{
		col = b->normal_color;
	}
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &b->bounds);
	size_t w, h;
	SDL_QueryTexture(b->label, NULL, NULL, &w, &h);
	size_t diffx = b->bounds.w - w;
	size_t diffy = b->bounds.h - h;
	SDL_Rect lpos = { b->bounds.x + diffx / 2, b->bounds.y + diffy / 2, w, h };
	SDL_RenderCopy(renderer, b->label, NULL, &lpos);
}

void button_update(button* b)
{
	if (b->blocked)
		return;

	size_t mx = mouse.x;
	size_t my = mouse.y;
	size_t x1 = b->bounds.x;
	size_t x2 = x1 + b->bounds.w;
	size_t y1 = b->bounds.y;
	size_t y2 = y1 + b->bounds.h;

	b->active = (mx >= x1 && mx < x2 && my >= y1 && my < y2);
	if (b->active && b->clicked && mouse.released)
	{
		b->action();
	}
	else if (b->active && mouse.pressed)
	{
		b->clicked = true;
	}
	else if (!mouse.current_state)
	{
		b->clicked = false;
	}
}