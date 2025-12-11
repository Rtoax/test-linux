// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/types.h>
#include <elf.h>
#include "utils.hpp"
#include "debug.h"
#include "memshow.c"


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
 *
 * WARNING: However, HPCC e_machine be recognized as Synopsys ARCv3 64-bit processor,
 * see:
 *      hpc/metax/samples$ readelf -h fatbin0.elf
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
	DEBUG_DBG("ehdr: ABI version %d, type %d, machine %s(%d), version %d, "
		  "entry %ld, phoff 0x%lx, "
		  "shoff 0x%lx, flags 0x%x, ehsize %d, phentsize %d, phnum %d, "
		  "shentsize %d, shnum %d, shstrndx %d\n",
		  ehdr->e_ident[EI_ABIVERSION],
		  ehdr->e_type,
		  str_e_machine(ehdr->e_machine), ehdr->e_machine,
		  ehdr->e_version, ehdr->e_entry,
		  ehdr->e_phoff, ehdr->e_shoff, ehdr->e_flags, ehdr->e_ehsize,
		  ehdr->e_phentsize, ehdr->e_phnum,
		  ehdr->e_shentsize, ehdr->e_shnum,
		  ehdr->e_shstrndx);
}
