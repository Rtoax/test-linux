// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao
/**
 * CXL Fixed Memory Window Structure (CFMWS)
 * CXL 3.0 Specification, Section 9.17.1.3, Table 9-22.
 *
 * Abbrev:
 * - NIW: Number of Interleave Ways
 */
#pragma once
#include <stdint.h>

struct cfmws {
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
};

void display_cfmws(struct cfmws *cfmws);
