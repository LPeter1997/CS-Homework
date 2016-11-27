#ifndef __MAP_REPR_H__
#define __MAP_REPR_H__

#include <SDL.h>
#include <stddef.h>
#include <stdint.h>
#include "tile.h"

typedef struct __layer
{
	TileID** grid;
	struct __layer* prev;
	struct __layer* next;
} layer;

typedef struct
{
	size_t width;
	size_t height;
	size_t xoff;
	size_t yoff;
	layer* layers_head;
	layer* current_layer;
	int selx;
	int sely;
} map;

void map_create(map*, size_t, size_t);
void map_offset_by(map*, int, int);
void map_render(map*, SDL_Renderer*);
void map_sel(map*, int, int);
void map_plot(map*, TileID);
void map_add_layer(map*);

#endif /* __MAP_REPR_H__ */