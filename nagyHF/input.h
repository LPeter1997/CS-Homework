#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>

struct
{
	size_t x;
	size_t y;
	bool current_state	: 1;
	bool last_state		: 1;
	bool pressed		: 1;
	bool released		: 1;
} mouse;

struct
{
	char last_typed;
	bool typed;
} keyboard;

#endif
