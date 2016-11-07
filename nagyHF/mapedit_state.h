#ifndef __MAPEDIT_ST_H__
#define __MAPEDIT_ST_H__

#include "game_state.h"

game_state mapedit_create(void);
void mapedit_init(void*);
void mapedit_update(void);
void mapedit_render(void*);
void mapedit_terminate(void);

#endif /* __MAPEDIT_ST_H__ */