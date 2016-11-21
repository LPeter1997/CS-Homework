#ifndef __MAPEDIT_ST_H__
#define __MAPEDIT_ST_H__

#include "game_state.h"

typedef struct
{
	size_t w, h;
	void* renderer;
} me_initializer;

game_state mapedit_create(void);
void mapedit_init(void*);
void mapedit_update(void);
void mapedit_render(void*);
void mapedit_terminate(void);

#endif /* __MAPEDIT_ST_H__ */