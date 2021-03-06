#ifndef __MBUTTON_H__
#define __MBUTTON_H__

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

struct __button;
typedef void(*callback)(struct __button*);

typedef struct __button
{
	SDL_Rect bounds;
	SDL_Rect l_bounds;
	SDL_Color normal_color;
	SDL_Color hilight_color;
	SDL_Color pressed_color;
	SDL_Texture* label;
	bool active;
	bool clicked;
	callback action;
	bool blocked;
	void* userdata;
} button;

void button_create(button*, SDL_Rect, SDL_Color, SDL_Color, SDL_Color, SDL_Texture*, callback);
void button_render(button*, SDL_Renderer*);
void button_update(button*);

#endif /* __MBUTTON_H__ */
