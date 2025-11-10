#pragma once

#include <stdio.h>
#include <ctype.h>

void memdump(FILE *f, const char *title, const void *buf, unsigned int len);
void fhexdump(FILE *fp, const char *pfx, const void *mem, size_t size);
void hexdump(const void *mem, size_t size);
