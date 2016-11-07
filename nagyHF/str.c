#include <string.h>
#include <stdlib.h>
#include "str.h"

void string_new(string* str, size_t init)
{
	str->reserved = init + 1;
	str->len = 0;
	str->data = (char*)malloc(str->reserved);
	str->data[0] = '\0';
}

void string_del(string* str)
{
	free(str->data);
	str->len = 0;
	str->reserved = 0;
}

void string_addc(string* str, char c)
{
	if (str->len == str->reserved - 1)
	{
		str->reserved *= 2;
		str->data = realloc(str->data, str->reserved);
	}

	str->data[str->len++] = c;
	str->data[str->len] = '\0';
}

void string_remc(string* str, size_t at)
{
	memcpy(&str->data[at], &str->data[at + 1], str->len - at);
	str->len--;
}