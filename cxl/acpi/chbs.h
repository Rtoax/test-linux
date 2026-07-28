// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao
/**
 * CXL Host Bridge Structure (CHBS)
 * CXL 2.0 Specification, Section 9.14.1.2
 * CXL 3.0 Specification, Section 9.17.1.2
 *
 * see also:
 * - /sys/bus/acpi/devices/ACPI0016:*
 * - $ qemu -device pxb-cxl ...
 */
#pragma once
#include <stdint.h>

struct chbs {
	uint8_t type;
	uint8_t reserved;
	uint16_t record_length;
	uint32_t uid;
	/**
	 * 00h: CXL 1.1 Specification compliant Host Bridge
	 * 01h: CXL 2.0 Specification compliant Host Bridge
	 */
	uint32_t cxl_version;
	uint32_t reserved2;
	/**
	 * If Version = 0, this represents the base address of
	 * CXL 1.1 Downstream Port RCRB.
	 *
	 * If version =1, this represents the base address of
	 * the CXL 2.0 CHBCR.
	 */
	uint64_t base;
	uint64_t length;
} __attribute__((packed));

void display_chbs(struct chbs *chbs);
