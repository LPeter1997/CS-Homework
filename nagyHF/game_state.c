#include <stdint.h>
#include <SDL.h>
#include "game_state.h"

static game_state state_stack[10];
static int stack_ptr = -1;

void gsm_update(void)
{
	state_stack[stack_ptr].update();
}

void gsm_render(void* userptr)
{
	state_stack[stack_ptr].render(userptr);
}

void gsm_push(game_state st, void* userptr)
{
	st.init(userptr);
	state_stack[++stack_ptr] = st;
}

void gsm_pop(void)
{
	state_stack[stack_ptr--].terminate();
}