#include <ctype.h>
#include "mapedit_state.h"
#include "map.h"
#include "input.h"
#include "window.h"
#include "grid_selector.h"
#include "loader.h"
#include "tile.h"
#include "textfield.h"

static map mmap;
static grid_selector gridsel;
static button buttons[4];
static textfield layer_f;
static fontatlas* fieldatl;
static TTF_Font* fieldfont;

static bool layername_valid(char c)
{
	return isalnum(c) || c == '_';
}

static next_layer(void* a)
{
	if (mmap.current_layer->next)
	{
		mmap.current_layer = mmap.current_layer->next;
	}
}

static prev_layer(void* a)
{
	if (mmap.current_layer->prev)
	{
		mmap.current_layer = mmap.current_layer->prev;
	}
}

static new_layer(void* a)
{
	map_add_layer(&mmap);
}

static del_layer(void* a)
{
	
}

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
	tile_init(init->renderer);
	map_create(&mmap, init->w, init->h);
	grid_selector_create(&gridsel, WIND_W - HUD_WIDTH + 50, 200, 4, 3);
	grid_selector_add(&gridsel, 0, 0, TEX_LOOKUP[T_Ground]);
	grid_selector_add(&gridsel, 0, 1, TEX_LOOKUP[T_TriLU]);
	grid_selector_add(&gridsel, 1, 1, TEX_LOOKUP[T_TriRU]);
	grid_selector_add(&gridsel, 0, 2, TEX_LOOKUP[T_TriLD]);
	grid_selector_add(&gridsel, 1, 2, TEX_LOOKUP[T_TriRD]);
	gridsel.sel_btn = &gridsel.buttons[0];

	// Buttons
	SDL_Rect rect = { WIND_W - HUD_WIDTH + 50, 450, 32, 32 };
	SDL_Color norm = { 0x22, 0x22, 0x22, 0xff };
	SDL_Color hil = { 0xbb, 0xbb, 0xbb, 0xff };
	SDL_Color press = { 0x11, 0x11, 0x11, 0xff };
	SDL_Texture* tex1 = loader_texture("uparrow.png", init->renderer);
	button_create(&buttons[0], rect, norm, hil, press, tex1, next_layer);
	rect.x += GS_OFFSET + 32;
	SDL_Texture* tex2 = loader_texture("downarrow.png", init->renderer);
	button_create(&buttons[1], rect, norm, hil, press, tex2, prev_layer);
	rect.x += GS_OFFSET + 32;
	SDL_Texture* tex3 = loader_texture("plus.png", init->renderer);
	button_create(&buttons[2], rect, norm, hil, press, tex3, new_layer);
	rect.x += GS_OFFSET + 32;
	SDL_Texture* tex4 = loader_texture("minus.png", init->renderer);
	button_create(&buttons[3], rect, norm, hil, press, tex4, del_layer);

	// The layer counter
	fieldfont = loader_font("arial.ttf", 16);
	fieldatl = loader_fontatlas(fieldfont, init->renderer);

	textfield_create(&layer_f, WIND_W - HUD_WIDTH + 50, 420, fieldatl, 10, layername_valid);
}

void mapedit_update(void)
{
	size_t i;

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
				map_plot(&mmap, tile_getID(gridsel.sel_btn->label));
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
				map_plot(&mmap, tile_getID(gridsel.sel_btn->label));
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
	grid_selector_update(&gridsel);
	for (i = 0; i < 4; i++)
	{
		button_update(&buttons[i]);
	}
	textfield_update(&layer_f);
}

void mapedit_render(void* renderer)
{
	size_t i;
	map_render(&mmap, renderer);
	SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, 0xff);
	SDL_Rect rect = { WIND_W - HUD_WIDTH, 0, HUD_WIDTH, WIND_H };
	SDL_RenderFillRect(renderer, &rect);
	grid_selector_render(&gridsel, renderer);
	for (i = 0; i < 4; i++)
	{
		button_render(&buttons[i], renderer);
	}
	textfield_draw(&layer_f, renderer);
}

void mapedit_terminate(void)
{

}