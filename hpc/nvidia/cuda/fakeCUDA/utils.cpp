// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/types.h>
#include <elf.h>
#include "utils.hpp"
#include "debug.h"


/**
 * like $ hexdump --canonical $FILE
 */
void hexdump(const void *mem, size_t size)
{
	const int width = 16;
	int nr_newline = 0;
	int nr_startline = 0;
	size_t align_size = 0;

	assert(!(width % 8) && "width must align of 8");

	while (align_size < size)
		align_size += width;

	for (size_t i = 0; i < size; i++) {
		bool startline = i % width == 0;
		bool newline = (i + 1) % width == 0;

		if (startline) {
			printf("%#016x | ", (uint64_t)mem + width * nr_newline);
		}

		uint8_t u8 = *(uint8_t *)((uint8_t *)mem + i);
		printf("%02x%s", u8, newline ? " |" : " ");

		if ((i + 1) % 8 == 0 && !newline)
			printf(" ");

		/**
		 * Display memory as character
		 */
		if (newline) {
			const void *memch = (uint8_t *)mem + width * nr_newline;
			for (size_t j = 0; j < width; j++) {
				uint8_t c8 = *(uint8_t *)((uint8_t *)memch + j);
				printf("%c", isprint(c8) ? c8 : '.');
			}
			printf("|\n");
		}

		if (newline)
			nr_newline++;
		if (startline)
			nr_startline++;
	}

	if (align_size > size) {
		for (size_t i = 0; i < align_size - size; i++)
			printf("   ");
		printf("|");

		const void *memlastrow = (uint8_t *)mem + width * nr_newline;
		for (size_t i = 0; i < width - (align_size - size); i++) {
			uint8_t c8 = *(uint8_t *)((uint8_t *)memlastrow + i);
			printf("%c", isprint(c8) ? c8 : '.');
		}
		for (size_t i = 0; i < align_size - size; i++)
			printf(" ");
		printf("|");
	}

	if (nr_newline != nr_startline)
		printf("\n");
}

void debug_hexdump(const void *mem, size_t size)
{
	if (!fakecuda_debug)
		return;
	hexdump(mem, size);
}

void output_memory_to_file(const char *file, const void *mem, size_t size)
{
	FILE *fp = fopen(file, "w");
	if (!fp) {
		LOG_ERROR("Open(%s) failed\n", file);
		return;
	}

	fwrite(mem, size, 1, fp);

	fclose(fp);
}

void dump_memory_to_file(const char *file, const void *mem, size_t size)
{
	if (!fakecuda_dump)
		return;
	output_memory_to_file(file, mem, size);
}

bool elf64_magic(const Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	    ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	    ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	    ehdr->e_ident[EI_MAG3] != ELFMAG3)
		return false;
	return true;
}

static const struct {
	Elf64_Half	e_machine;
	const char	*name;
} string_e_machines[] = {
	{ EM_CUDA /* 190 */, "NVIDIA CUDA" },
	{ EM_AMDGPU /* 224, HIP/ROCm */, "AMDGPU" },
/**
 * FIXME: Not found 253 in anywhere, even https://sourceware.org/git/glibc,
 * 253 just dump from ELF file. By the way, 252 is EM_CSKY, 258 is EM_LOONGARCH.
 */
#ifndef EM_HPCC_GPU
#define EM_HPCC_GPU	253
#endif
	{ EM_HPCC_GPU, "HPCC GPU" },
};

static const char *str_e_machine(Elf64_Half machine)
{
	for (int i = 0; i < ARRAY_SIZE(string_e_machines); i++)
		if (string_e_machines[i].e_machine == machine)
			return string_e_machines[i].name;
	return "unknown";
}

void elf64_dump_ehdr(const Elf64_Ehdr *ehdr)
{
	DEBUG_DBG("ehdr: ABI version %d, type %ld, machine %s(%ld), version %ld, "
		  "entry %ld, phoff 0x%lx, "
		  "shoff 0x%lx, flags 0x%lx, ehsize %ld, phentsize %ld, phnum %ld, "
		  "shentsize %ld, shnum %ld, shstrndx %ld\n",
		  ehdr->e_ident[EI_ABIVERSION],
		  ehdr->e_type,
		  str_e_machine(ehdr->e_machine), ehdr->e_machine,
		  ehdr->e_version, ehdr->e_entry,
		  ehdr->e_phoff, ehdr->e_shoff, ehdr->e_flags, ehdr->e_ehsize,
		  ehdr->e_phentsize, ehdr->e_phnum,
		  ehdr->e_shentsize, ehdr->e_shnum,
		  ehdr->e_shstrndx);
}
