// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://github.com/ROCm/rocm-systems.git
 * - https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html
 */
#pragma once
#include <stdint.h>

/**
 * /usr/local/cuda-13.0/targets/x86_64-linux/include/fatbinary_section.h
 */
#define FATBINC_MAGIC   0x466243B1
#define FATBINC_VERSION 1
#define FATBINC_LINK_VERSION 2


/**
 * https://github.com/ROCm/rocm-systems.git
 * clr/hipamd/src/hip_platform.cpp
 *
 * /usr/local/cuda-13.0/targets/x86_64-linux/include/fatbinary_section.h
 */
struct __CudaFatBinaryWrapper {
	unsigned int magic;
	unsigned int version;
	void *fatbin;
	void *dummy1;
};

/**
 * https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html
 * https://github.com/n-eiling/cuda-fatbin-decompression/blob/master/fatbin-decompress.h
 */
struct fatBinaryHeader {
	uint32_t magic;
	uint16_t version;
	uint16_t header_size;
	uint64_t data_size;
};

/**
 * https://github.com/n-eiling/cuda-fatbin-decompression/blob/master/fatbin-decompress.h
 */
struct fatBinaryTextHeader {
	uint16_t kind;
	uint16_t unknown1;
	uint32_t header_size;
	uint64_t size;
	uint32_t compressed_size;
	/* Address size for PTX? */
	uint32_t unknown2;
	uint16_t minor;
	uint16_t major;
	uint32_t arch;
	uint32_t obj_name_offset;
	uint32_t obj_name_len;
	uint64_t flags;
	/* Alignment for compression? */
	uint64_t zero;
	/* Length of compressed data in decompressed representation.
	 * There is an uncompressed footer so this is generally smaller
	 * than size. */
	uint64_t decompressed_size;
};


void fatbinParser(const struct fatBinaryHeader *fatbin);
