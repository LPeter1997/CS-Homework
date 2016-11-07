#include "menu_state.h"
#include "button.h"
#include "loader.h"

#define BUTTON_CNT 2

static button buttons[BUTTON_CNT];
SDL_Texture* background;

static void menu_newlvl(void);
static void menu_lodlvl(void);

game_state menu_create(void)
{
	game_state st;
	st.init = menu_init;
	st.update = menu_update;
	st.render = menu_render;
	st.terminate = menu_terminate;
	return st;
}

void menu_init(void* renderer)
{
	background = loader_texture("izse.png", renderer);
	TTF_Font* fnt = loader_font("arial.ttf", 48);
	SDL_Color white = { 0xff, 0xff, 0xff, 0xff };
	SDL_Texture* label1 = loader_font2text("New Level", fnt, white, renderer);
	SDL_Texture* label2 = loader_font2text("Load Level", fnt, white, renderer);
	size_t w = 250;
	size_t h = 90;
	SDL_Rect rect = { 960 / 2 - w / 2, 100, w, h };
	SDL_Color col = { 0xff, 0x0, 0x0, 0xff };
	SDL_Color hicol = { 0xff, 0x88, 0x88, 0xff };
	SDL_Color prcol = { 0xaa, 0x0, 0x0, 0xff };
	button_create(&buttons[0], rect, col, hicol, prcol, label1, menu_newlvl);
	rect.y += 120;
	button_create(&buttons[1], rect, col, hicol, prcol, label2, menu_lodlvl);
	loader_font_u(fnt);
}

void menu_update(void)
{
	size_t i;
	for (i = 0; i < BUTTON_CNT; i++)
	{
		button_update(&buttons[i]);
	}
}

void menu_render(void* renderer)
{
	size_t i;
	SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xff);
	SDL_RenderClear(renderer);
	SDL_Rect bgr = { 0, 0, 960, 540 };
	SDL_RenderCopy(renderer, background, NULL, &bgr);
	for (i = 0; i < BUTTON_CNT; i++)
	{
		button_render(&buttons[i], renderer);
	}
}

void menu_terminate(void)
{
	loader_texture_u(background);
	size_t i;
	for (i = 0; i < BUTTON_CNT; i++)
	{
		loader_texture_u(buttons[i].label);
	}
}

static void menu_newlvl(void)
{
	printf("New\n");
}

static void menu_lodlvl(void)
{
	printf("Load\n");
}