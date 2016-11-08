#include <SDL.h>
#include "mapsize_state.h"
#include "textfield.h"
#include "loader.h"
#include "button.h"

#define BUTTON_CNT 2

static textfield width_f;
static SDL_Texture* width_l;
static textfield height_f;
static SDL_Texture* height_l;
static fontatlas* fieldatl;
static TTF_Font* fieldfont;
static button buttons[BUTTON_CNT];

static void ms_create(void) {}
static void ms_back(void);

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
	SDL_Color white = { 0xff, 0xff, 0xff, 0xff };
	fieldfont = loader_font("arial.ttf", 32);
	fieldatl = loader_fontatlas(fieldfont, renderer);

	textfield_create(&width_f, 210, 200, fieldatl, 8);
	width_l = loader_font2text("Width:", fieldfont, white, renderer);
	
	textfield_create(&height_f, 210, 250, fieldatl, 8);
	height_l = loader_font2text("Height:", fieldfont, white, renderer);

	textfield_activate(&width_f);

	// Buttons
	SDL_Texture* label1 = loader_font2text("Create", fieldfont, white, renderer);
	SDL_Texture* label2 = loader_font2text("Back", fieldfont, white, renderer);
	size_t w = 250;
	size_t h = 40;
	SDL_Rect rect = { 450, 200, w, h };
	SDL_Color col = { 0xff, 0x0, 0x0, 0xff };
	SDL_Color hicol = { 0xff, 0x88, 0x88, 0xff };
	SDL_Color prcol = { 0xaa, 0x0, 0x0, 0xff };
	button_create(&buttons[0], rect, col, hicol, prcol, label1, ms_create);
	rect.y += 50;
	button_create(&buttons[1], rect, col, hicol, prcol, label2, ms_back);
}

void mapsize_update(void)
{
	size_t i = 0;
	textfield_update(&width_f);
	textfield_update(&height_f);

	for (i = 0; i < BUTTON_CNT; i++)
	{
		button_update(&buttons[i]);
	}
}

void mapsize_render(void* renderer)
{
	size_t i;
	SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xff);
	SDL_RenderClear(renderer);

	size_t w;
	size_t h;
	SDL_QueryTexture(width_l, NULL, NULL, &w, &h);
	SDL_Rect rect = { 100, 200, w, h };

	SDL_RenderCopy(renderer, width_l, NULL, &rect);
	textfield_draw(&width_f, renderer);

	SDL_QueryTexture(height_l, NULL, NULL, &w, &h);
	rect.w = w;
	rect.h = h;
	rect.y += 50;

	SDL_RenderCopy(renderer, height_l, NULL, &rect);
	textfield_draw(&height_f, renderer);

	for (i = 0; i < BUTTON_CNT; i++)
	{
		button_render(&buttons[i], renderer);
	}
}

void mapsize_terminate(void)
{
	loader_fontatlas_u(fieldatl);
	loader_texture_u(width_l);
	loader_font_u(fieldfont);
}

static void ms_back(void)
{
	gsm_pop();
}