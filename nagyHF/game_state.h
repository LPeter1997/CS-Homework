#ifndef __GSM_H__
#define __GSM_H__

#include <SDL.h>

typedef void(*userptr_callback)(void*);
typedef void(*callback)(void);

typedef struct
{
	userptr_callback init;
	callback update;
	userptr_callback render;
	callback terminate;
} game_state;

void gsm_update(void);
void gsm_render(void*);
void gsm_push(game_state, void*);
void gsm_pop(void);

#endif /* __GSM_H__ */