#include <SDL.h>
#include "mapsize_state.h"
#include "textfield.h"
#include "loader.h"

static textfield width_f;
static fontatlas* fieldatl;
static TTF_Font* fieldfont;

game_state mapsize_create(void)
{
	game_state st;
	st.init = mapsize_init;
	st.update = mapsize_update;
	st.render = mapsize_render;
	st.terminate = mapsize_terminate;
	return st;
}

void mapsize_init(void* renderer)
{
	fieldfont = loader_font("arial.ttf", 32);
	fieldatl = loader_fontatlas(fieldfont, renderer);
	textfield_create(&width_f, 200, 200, fieldatl, 20);

	textfield_activate(&width_f);
}

void mapsize_update(void)
{
	textfield_update(&width_f);
}

void mapsize_render(void* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xff);
	SDL_RenderClear(renderer);

	textfield_draw(&width_f, renderer);
}

void mapsize_terminate(void)
{
	loader_fontatlas_u(fieldatl);
	loader_font_u(fieldfont);
}