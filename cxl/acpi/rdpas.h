// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao
/**
 * RCEC Downstream Port Association Structure (RDPAS)
 * CXL 3.0 Specification, Section 9.17.1.5, Table 9-24.
 *
 * Abbrev:
 */
#pragma once
#include <stdint.h>

struct rdpas {
	uint8_t type;
	uint8_t reserved1;
	uint16_t record_length;
	uint16_t rcec_segment_num;
	uint16_t rcec_bdf;
	uint8_t protocol_type;
	uint64_t base_addr;
} __attribute__((packed));

void display_rdpas(struct rdpas *rdpas);
