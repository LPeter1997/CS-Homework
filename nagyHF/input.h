#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>

typedef struct
{
	bool current_state : 1;
	bool last_state : 1;
	bool pressed : 1;
	bool released : 1;
} mb;

typedef enum
{
	MB_Left, MB_Right,
	__MB_Cnt__
} MousePress;

struct
{
	size_t x;
	size_t y;
	mb buttons[__MB_Cnt__];
} mouse;

typedef enum
{
	KP_Up, KP_Down, KP_Left, KP_Right, KP_Shift,
	__KP_Cnt__
} KeyPress;

struct
{
	char last_typed;
	bool typed;
	mb keys[__KP_Cnt__];
} keyboard;

#endif
