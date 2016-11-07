#include "mapedit_state.h"

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

}

void mapedit_update(void)
{

}

void mapedit_render(void* renderer)
{

}

void mapedit_terminate(void)
{

}