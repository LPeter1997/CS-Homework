#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "loader.h"

#define IMAGE_FLAGS IMG_INIT_PNG

bool loader_init(void)
{
	if (!(IMG_Init(IMAGE_FLAGS) & IMAGE_FLAGS))
	{
		printf("Image loading initialization error: %s\n", IMG_GetError());
		return false;
	}
	if (TTF_Init() == -1)
	{
		printf("Font loading initialization error: %s\n", TTF_GetError());
		return false;
	}
	return true;
}

void loader_term(void)
{
	IMG_Quit();
}

SDL_Texture* loader_texture(const char* path, SDL_Renderer* renderer)
{
	SDL_Texture* tex = NULL;

	SDL_Surface* surf = IMG_Load(path);
	if (surf)
	{
		tex = SDL_CreateTextureFromSurface(renderer, surf);
		if (tex)
		{
			SDL_FreeSurface(surf);
			return tex;
		}
		else
		{
			printf("Could not create texture: %s\n", SDL_GetError());
		}
	}
	else
	{
		printf("Could not load image: '%s'. Error: %s\n", path, IMG_GetError());
	}

	return NULL;
}

void loader_texture_u(SDL_Texture* tex)
{
	SDL_DestroyTexture(tex);
}

TTF_Font* loader_font(const char* fnt, size_t sz)
{
	TTF_Font* ff =  TTF_OpenFont(fnt, sz);
	if (!ff)
	{
		printf("Could not load font '%s': %s\n", fnt, TTF_GetError());
		return NULL;
	}

	return ff;
}

void loader_font_u(TTF_Font* fnt)
{
	TTF_CloseFont(fnt);
}

SDL_Texture* loader_font2text(const char* text, TTF_Font* fnt, SDL_Color col, SDL_Renderer* renderer)
{
	SDL_Surface* surf = TTF_RenderText_Solid(fnt, text, col);
	SDL_Texture* texture;
	if (!surf)
	{
		printf("Could not draw text: %s\n", TTF_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (!texture)
	{
		printf("Could not make text texture: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_FreeSurface(surf);
	return texture;
}