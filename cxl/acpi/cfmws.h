// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao. All rights reserved.
/**
 * CXL Fixed Memory Window Structure (CFMWS)
 * CXL 3.0 Specification, Section 9.17.1.3, Table 9-22.
 * CXL 2.0 not support CFMWS.
 *
 * Abbrev:
 * - HPA: Host Physical Address
 * - NIW: Number of Interleave Ways
 */
#pragma once
#include <stdbool.h>
#include <stdint.h>

struct cfmws {
	/**
	 * 1 = indicates this is a CFMWS entry
	 */
	uint8_t type;
	uint8_t reserved;
	/**
	 * ::record_length = 0x24 + 4 * NIW
	 */
	uint16_t record_length;
	uint32_t reserved2;
	uint64_t base_hpa;
	uint64_t window_size;
	/**
	 * Encoded Number of Interleave Ways (ENIW)
	 *
	 * NIW is the raw count of Interleave ways whereas ENIW is the encoded
	 * value:
	 * - If ENIW <  8, NIW = 2^ENIW
	 * - If ENIW >= 8, NIW = 3 * 2^(ENIW - 8)
	 */
	uint8_t eniw;
	uint8_t interleave_arithmetic;
	uint8_t reserved3[2];
	/**
	 * Host Bridge Interleave Granularity (HBIG)
	 *
	 * The number of consecutive bytes within the interleave that are
	 * decoded by each target in the Interleave Target List represented in
	 * an encoded format.
	 *
	 * CXL 3.0 Specification, 8.2.4.19.7 CXL HDM Decoder n Control Register (Offset 20h*n+20h)
	 * - Interleave Granularity size: 256, 512, 1k, 2k, 4k, 8k, 16k
	 *
	 * - 0h – 256 Bytes
	 * - 1h – 512 Bytes
	 * - 2h – 1024 Bytes (1 KB)
	 * - 3h – 2048 Bytes (2 KB)
	 * - 4h – 4096 Bytes (4 KB)
	 * - 5h – 8192 Bytes (8 KB)
	 * - 6h – 16384 Bytes (16 KB)
	 * - All other – Reserved
	 */
	uint32_t hbig;
	uint16_t window_restrictions;
	/* QTAG ID */
	uint16_t qtag_id;
	/**
	 * A list of all the Interleave Targets.
	 * size = 4 * NIW
	 */
	uint32_t interleave_target_list[];
} __attribute__((packed));

void display_cfmws(struct cfmws *cfmws, bool with_title);
