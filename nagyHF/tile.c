#include <stddef.h>
#include "tile.h"
#include "loader.h"

void tile_init(SDL_Renderer* renderer)
{
	TEX_LOOKUP[T_Air] = NULL;
	TEX_LOOKUP[T_Ground] = loader_texture("Block.png", renderer);
	TEX_LOOKUP[T_TriLD] = loader_texture("Tri_LD.png", renderer);
	TEX_LOOKUP[T_TriLU] = loader_texture("Tri_LU.png", renderer);
	TEX_LOOKUP[T_TriRD] = loader_texture("Tri_RD.png", renderer);
	TEX_LOOKUP[T_TriRU] = loader_texture("Tri_RU.png", renderer);
}

TileID tile_getID(SDL_Texture* tex)
{
	size_t i;
	for (i = 0; i < __Texture_Cnt__; i++)
	{
		if (TEX_LOOKUP[i] == tex)
		{
			return (TileID)i;
		}
	}
}