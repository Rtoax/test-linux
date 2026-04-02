#pragma once
#include <sys/types.h>

int read_off(int fd, off_t off, void *buf, size_t size, bool keepoff);
