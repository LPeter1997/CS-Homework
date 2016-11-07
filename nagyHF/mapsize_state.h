#ifndef __MAPSIZE_ST_H__
#define __MAPSIZE_ST_H__

#include "game_state.h"

game_state mapsize_create(void);
void mapsize_init(void*);
void mapsize_update(void);
void mapsize_render(void*);
void mapsize_terminate(void);

#endif /* __MAPSIZE_ST_H__ */
