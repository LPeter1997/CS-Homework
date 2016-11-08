#ifndef __FONTATLAS_H__
#define __FONTATLAS_H__

#include <SDL.h>

#define ATLAS_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .:,;3-*/<>()|"
#define ATLAS_LEN (sizeof(ATLAS_CHARS) - 1)

typedef struct
{
	size_t w;
	size_t h;
	SDL_Texture* texture;
} glyph;

typedef struct
{
	size_t pt;
	size_t w;
	size_t h;
	glyph chars[ATLAS_LEN];
} fontatlas;

void atlas_draw(fontatlas*, size_t, size_t, const char*, SDL_Color, SDL_Renderer*);
void atlas_drawn(fontatlas*, size_t, size_t, const char*, size_t, SDL_Color, SDL_Renderer*);

#endif /* __FONTATLAS_H__ */