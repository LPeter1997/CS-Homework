#include "mapedit_state.h"
#include "map.h"
#include "input.h"
#include "window.h"

static map mmap;

game_state mapedit_create(void)
{
	game_state st;
	st.init = mapedit_init;
	st.update = mapedit_update;
	st.render = mapedit_render;
	st.terminate = mapedit_terminate;
	return st;
}

void mapedit_init(void* userptr)
{
	me_initializer* init = userptr;
	map_create(&mmap, init->w, init->h);
}

void mapedit_update(void)
{
	if (SDL_GetTicks() % 4 == 0)
	{
		int dx = 0;
		int dy = 0;
		
		if (keyboard.keys[KP_Up].current_state) dy--;
		if (keyboard.keys[KP_Down].current_state) dy++;
		if (keyboard.keys[KP_Left].current_state) dx--;
		if (keyboard.keys[KP_Right].current_state) dx++;

		map_offset_by(&mmap, dx, dy);
	}

	if (mouse.x < WIND_W - HUD_WIDTH)
	{
		if (keyboard.keys[KP_Shift].current_state)
		{
			if (mouse.buttons[MB_Left].current_state)
			{
				map_plot(&mmap, T_Ground);
			}
			else if (mouse.buttons[MB_Right].current_state)
			{
				map_plot(&mmap, T_Air);
			}
		}
		else
		{
			if (mouse.buttons[MB_Left].released)
			{
				map_plot(&mmap, T_Ground);
			}
			else if (mouse.buttons[MB_Right].released)
			{
				map_plot(&mmap, T_Air);
			}
		}

		map_sel(&mmap, mouse.x, mouse.y);
	}
	else
	{
		map_sel(&mmap, -1, -1);
	}
}

void mapedit_render(void* renderer)
{
	map_render(&mmap, renderer);
	SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, 0xff);
	SDL_Rect rect = { WIND_W - HUD_WIDTH, 0, HUD_WIDTH, WIND_H };
	SDL_RenderFillRect(renderer, &rect);

}

void mapedit_terminate(void)
{

}