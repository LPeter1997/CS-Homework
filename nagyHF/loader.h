#ifndef __LOADER_H__
#define __LOADER_H__

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

bool loader_init(void);
void loader_term(void);
SDL_Texture* loader_texture(const char*, SDL_Renderer*);
void loader_texture_u(SDL_Texture*);
TTF_Font* loader_font(const char*, size_t);
void loader_font_u(TTF_Font*);
SDL_Texture* loader_font2text(const char*, TTF_Font*, SDL_Color, SDL_Renderer*);

#endif /* __LOADER_H__ */