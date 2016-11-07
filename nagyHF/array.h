#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

typedef struct
{
	void** data;
	size_t size;
	size_t reserved;
} array;

void array_new(array*, size_t);
void array_push(array*, void*);
void array_erase(array*, size_t);
void array_del(array*);

#endif /* __ARRAY_H__ */
