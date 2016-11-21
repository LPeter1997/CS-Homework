#ifndef __MAP_REPR_H__
#define __MAP_REPR_H__

#include <SDL.h>
#include <stddef.h>
#include <stdint.h>
#include "tile.h"

typedef struct
{
	size_t width;
	size_t height;
	size_t xoff;
	size_t yoff;
	TileID** grid;
} map;

void map_create(map*, size_t, size_t);
void map_offset_by(map*, size_t, size_t);
void map_render(map*, SDL_Renderer*);

#endif /* __MAP_REPR_H__ */