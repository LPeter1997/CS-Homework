#include <stdlib.h>
#include <string.h>
#include "array.h"

void array_new(array* arr, size_t init)
{
	arr->data = (void**)malloc(init);
	arr->size = 0;
	arr->reserved = init;
}

void array_push(array* arr, void* element)
{
	if (arr->size == arr->reserved)
	{
		arr->reserved *= 2;
		arr->data = realloc(arr->data, arr->reserved);
	}

	arr->data[arr->size++] = element;
}

void array_erase(array* arr, size_t idx)
{
	arr->size--;
	memcpy(arr->data + idx, arr->data + idx + 1, arr->size - idx);
	if (arr->size < arr->reserved / 4)
	{
		arr->reserved /= 2;
		arr->data = realloc(arr->data, arr->reserved);
	}
}

void array_del(array* arr)
{
	arr->size = 0;
	arr->reserved = 0;
	free(arr->data);
}