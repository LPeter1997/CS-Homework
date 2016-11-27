#ifndef __TILE_H__
#define __TILE_H__

#include <SDL.h>

#define TILE_SIZE 64

typedef enum
{
	T_Air = 0,
	T_Ground,
	T_TriLD,
	T_TriRD,
	T_TriLU,
	T_TriRU,
	__Texture_Cnt__
} TileID;

SDL_Texture* TEX_LOOKUP[(int)__Texture_Cnt__];

void tile_init(SDL_Renderer*);
TileID tile_getID(SDL_Texture*);

#endif /* __TILE_H__ */