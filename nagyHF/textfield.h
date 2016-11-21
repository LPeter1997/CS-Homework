#ifndef __TEXTFIELD_H__
#define __TEXTFIELD_H__

#include <stdbool.h>
#include "fontatlas.h"
#include "str.h"

typedef bool(*validator)(char);

typedef struct
{
	SDL_Rect bounds;
	string buffer;
	fontatlas* font;
	bool active;
	validator valid;
} textfield;

void textfield_create(textfield*, size_t, size_t, fontatlas*, size_t, validator);
void textfield_del(textfield*);
void textfield_draw(textfield*, SDL_Renderer*);
void textfield_update(textfield*);
void textfield_activate(textfield*);
void textfield_deactivate(textfield*);

#endif /* __TEXTFIELD_H__ */