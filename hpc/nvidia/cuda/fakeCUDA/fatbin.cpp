// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html
 */
#include <elf.h>
#include <string.h>
#include "utils.hpp"
#include "fatbin.hpp"
#include "fatbin-hip.hpp"
#include "debug.h"


void fatbinParser(const struct fatBinaryHeader *fatbin)
{
	const struct fatBinaryTextHeader *textHdr;
	const struct ClangOffloadBundleUncompressedHeader *hipHdr;

	/**
	 * The Fatbin is HIP like format.
	 */
	hipHdr = (struct ClangOffloadBundleUncompressedHeader *)fatbin;
	if (!strncmp(hipHdr->magic, kOffloadBundleUncompressedMagicStr,
		     kOffloadBundleUncompressedMagicStrSize - 1)) {
		DEBUG_WARN("Found HIP Fatbin, %s\n", hipHdr->magic);
		hipFatbinParser(hipHdr);
		return;
	}

	DEBUG_DBG("fatbin: magic %x, version %d, header_size %d, data_size %d\n",
		  fatbin->magic, fatbin->version, fatbin->header_size,
		  fatbin->data_size);

	debug_memdump(fatbin, fatbin->header_size);

	textHdr = (struct fatBinaryTextHeader *)((uint8_t *)fatbin + fatbin->header_size);
	DEBUG_DBG("textHdr: kind %d, header_size %d, size %ld, "
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

	/**
	 * Here, we got CUDA machine
	 */
	if (ehdr->e_machine != EM_CUDA) {
		DEBUG_DBG("Fatbin elf is not NVIDIA CUDA architecture\n");
		goto skip_elf;
	}

	elf64_dump_ehdr(ehdr);

	debug_memdump(ehdr, sizeof(*ehdr));
skip_elf:

	return;
}

/**
 * https://github.com/ROCm/rocm-systems
 * ROCm/rocm-systems/projects/clr/hipamd/src/hip_comgr_helper.cpp
 */
void hipFatbinParser(const struct ClangOffloadBundleUncompressedHeader *obheader)
{
	DEBUG_DBG("HIP obheader: magic %s, numOfCodeObjects %d\n",
		  obheader->magic, obheader->numOfCodeObjects);

	const struct ClangOffloadBundleInfo *desc = &obheader->desc[0];

	for (int i = 0; i < obheader->numOfCodeObjects; i++) {
		DEBUG_DBG("entry %d: offset 0x%lx, size %ld, bundleEntryIdSize %ld\n",
			  i, desc->offset, desc->size, desc->bundleEntryIdSize);

		/* Getn next desc */
		desc = (const struct ClangOffloadBundleInfo *)(&desc->bundleEntryId[0] + desc->bundleEntryIdSize);

		const void *image = (const uint8_t *)obheader + desc->offset;
		const size_t image_size = desc->size;

		DEBUG_DBG("image %p, image_size %ld\n", image, image_size);

		if (elf64_magic((const Elf64_Ehdr *)image)) {
			debug_memdump(image, sizeof(Elf64_Ehdr));
			elf64_dump_ehdr((Elf64_Ehdr *)image);
			break;
		}
	}

	return;
}
