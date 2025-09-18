// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html
 */
#include <elf.h>
#include "utils.hpp"
#include "fatbin.hpp"
#include "debug.h"


void fatbinParser(const struct fatBinaryHeader *fatbin)
{
	const struct fatBinaryHeader *fatBinHdr = fatbin;
	const struct fatBinaryTextHeader *textHdr;

	LOG_DEBUG("fatbin: magic %x, version %d, header_size %d, data_size %d\n",
		  fatBinHdr->magic, fatBinHdr->version, fatBinHdr->header_size,
		  fatBinHdr->data_size);

	debug_memdump(fatBinHdr, fatBinHdr->header_size);

	textHdr = (struct fatBinaryTextHeader *)((uint8_t *)fatBinHdr + fatBinHdr->header_size);
	LOG_DEBUG("textHdr: kind %d, header_size %d, size %ld, "
		  "compressed_size %d, decompressed_size %d, "
		  "minor %d, major %d, arch %d, obj_name_offset %d, obj_name_len %d, "
		  "flags 0x%lx\n",
		  textHdr->kind, textHdr->header_size, textHdr->size,
		  textHdr->compressed_size, textHdr->decompressed_size,
		  textHdr->minor, textHdr->major,
		  textHdr->arch,
		  textHdr->obj_name_offset, textHdr->obj_name_len,
		  textHdr->flags);

	debug_memdump(textHdr, textHdr->header_size);

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)((uint8_t *)textHdr + textHdr->header_size);

	if (ehdr->e_machine != 190) {
		LOG_ERROR("Fatbin elf is not NVIDIA CUDA architecture\n");
		goto skip_elf;
	}

	LOG_DEBUG("ehdr: type %ld, machine %ld, version %ld, entry %ld, phoff 0x%lx, "
		  "shoff 0x%lx, flags 0x%lx, ehsize %ld, phentsize %ld, phnum %ld, "
		  "shentsize %ld, shnum %ld, shstrndx %ld\n",
		  ehdr->e_type, ehdr->e_machine, ehdr->e_version, ehdr->e_entry,
		  ehdr->e_phoff, ehdr->e_shoff, ehdr->e_flags, ehdr->e_ehsize,
		  ehdr->e_phentsize, ehdr->e_phnum,
		  ehdr->e_shentsize, ehdr->e_shnum,
		  ehdr->e_shstrndx);

	debug_memdump(ehdr, sizeof(*ehdr));
skip_elf:

	return;
}
