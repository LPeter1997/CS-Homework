#ifndef __MENU_ST_H__
#define __MENU_ST_H__

#include <SDL.h>
#include "game_state.h"

game_state menu_create(void);
void menu_init(void*);
void menu_update(void);
void menu_render(void*);
void menu_terminate(void);

#endif /* __MENU_ST_H__ */
