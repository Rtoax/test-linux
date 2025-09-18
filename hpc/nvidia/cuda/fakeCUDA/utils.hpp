// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <sys/types.h>

#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))

void memdump(const void *mem, size_t size);
void debug_memdump(const void *mem, size_t size);

bool elf64_magic(const Elf64_Ehdr *ehdr);
void elf64_dump_ehdr(const Elf64_Ehdr *ehdr);
