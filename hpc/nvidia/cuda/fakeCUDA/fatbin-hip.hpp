// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <stdint.h>

struct ClangOffloadBundleInfo {
	uint64_t offset;
	uint64_t size;
	uint64_t bundleEntryIdSize;
	const char bundleEntryId[1];
};

/**
 * https://github.com/ROCm/rocm-systems
 * ROCm/rocm-systems/projects/clr/hipamd/src/hip_code_object.hpp
 */
struct ClangOffloadBundleUncompressedHeader {
#define	kOffloadBundleUncompressedMagicStr	"__CLANG_OFFLOAD_BUNDLE__"
#define kOffloadBundleUncompressedMagicStrSize	sizeof(kOffloadBundleUncompressedMagicStr)
	const char magic[kOffloadBundleUncompressedMagicStrSize - 1];
	uint64_t numOfCodeObjects;
	struct ClangOffloadBundleInfo desc[1];
};

// Clang Offload bundler description & Header in compressed mode.
struct ClangOffloadBundleCompressedHeader {
#define kOffloadBundleCompressedMagicStr	"CCOB"
#define kOffloadBundleCompressedMagicStrSize	sizeof(kOffloadBundleCompressedMagicStr)
	const char magic[kOffloadBundleCompressedMagicStrSize - 1];
	uint16_t versionNumber;
	uint16_t compressionMethod;
	uint32_t totalSize;
	uint32_t uncompressedBinarySize;
	uint64_t Hash;
	const char compressedBinarydesc[1];
};


void hipFatbinParser(const struct ClangOffloadBundleUncompressedHeader *offload);
