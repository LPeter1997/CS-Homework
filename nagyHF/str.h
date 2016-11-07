#ifndef __STR_H__
#define __STR_H__

#include <stddef.h>

typedef struct
{
	char* data;
	size_t len;
	size_t reserved;
} string;

void string_new(string*, size_t);
void string_del(string*);
void string_addc(string*, char);
void string_remc(string*, size_t);

#endif /* __STR_H__ */