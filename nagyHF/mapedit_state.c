#include "mapedit_state.h"
#include "map.h"
#include "input.h"

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
	if (SDL_GetTicks() % 10 == 0)
	{
		int dx = 0;
		int dy = 0;
		
		if (keyboard.keys[KP_Up].current_state) dy--;
		if (keyboard.keys[KP_Down].current_state) dy++;
		if (keyboard.keys[KP_Left].current_state) dx--;
		if (keyboard.keys[KP_Right].current_state) dx++;

		map_offset_by(&mmap, dx, dy);
	}

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

void mapedit_render(void* renderer)
{
	map_render(&mmap, renderer);
}

void mapedit_terminate(void)
{

}