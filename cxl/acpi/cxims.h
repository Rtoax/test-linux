// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao
/**
 * CXL XOR Interleave Math Structure (CXIMS)
 * CXL 3.0 Specification, Section 9.17.1.4, Table 9-23.
 *
 * Abbrev:
 * - NIB: Number of Bitmap Entries
 */
#pragma once
#include <stdint.h>

struct cxims {
	uint8_t type;
	uint8_t reserved1;
	uint16_t record_length;
	uint16_t reserved2;
	uint8_t hbig;
	uint8_t nib;
	/* 8 * NIB */
	uint8_t xormap_list[];
};

void display_cxims(struct cxims *cxims);
