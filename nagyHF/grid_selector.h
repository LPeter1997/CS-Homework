#ifndef __GRIDSEL_H__
#define __GRIDSEL_H__

#include <stddef.h>
#include <SDL.h>
#include "button.h"

#define GS_SIZE 48
#define GS_ISIZE 8
#define GS_OFFSET 8
#define GS_STROKE 8

typedef struct
{
	size_t x;
	size_t y;
	size_t width;
	size_t height;
	int sel_x;
	int sel_y;
	button* buttons;
	button* sel_btn;
} grid_selector;

void grid_selector_create(grid_selector*, size_t, size_t, size_t, size_t);
void grid_selector_add(grid_selector*, size_t, size_t, SDL_Texture*);
void grid_selector_update(grid_selector*);
void grid_selector_render(grid_selector*, SDL_Renderer*);

#endif /* __GRIDSEL_H__ */