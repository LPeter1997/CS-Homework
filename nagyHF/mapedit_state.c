#include "mapedit_state.h"
#include "map.h"

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
		map_offset_by(&mmap, 1, 1);
	}
}

void mapedit_render(void* renderer)
{
	map_render(&mmap, renderer);
}

void mapedit_terminate(void)
{

}