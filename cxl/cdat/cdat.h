// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * CXL CDAT (Coherent Device Attribute Table) Structure
 *
 * Refs:
 * - https://git.zx2c4.com/qemu/plain/include/hw/cxl/cxl_cdat.h
 * - https://docs.kernel.org/driver-api/cxl/platform/cdat.html
 */
#pragma once
#include <stdint.h>

/* CDAT Table Format - CDAT Table 1 */
struct cdat_tab_hdr {
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	uint8_t reserved[6];
	uint32_t sequence;
} __attribute__((packed));

/* CDAT Structure Types - CDAT Table 2 */
enum cdat_type {
	CDAT_TYPE_DSMAS = 0,
	CDAT_TYPE_DSLBIS = 1,
	CDAT_TYPE_DSMSCIS = 2,
	CDAT_TYPE_DSIS = 3,
	CDAT_TYPE_DSEMTS = 4,
	CDAT_TYPE_SSLBIS = 5,
};

typedef struct cdat_sub_hdr {
	uint8_t type;
	uint8_t reserved;
	uint16_t length;
} __attribute__((packed)) CDATSubHeader;

/* Device Scoped Memory Affinity Structure - CDAT Table 3 */
typedef struct CDATDsmas {
	CDATSubHeader header;
	uint8_t DSMADhandle;
	uint8_t flags;
#define CDAT_DSMAS_FLAG_NV (1 << 2)
#define CDAT_DSMAS_FLAG_SHAREABLE (1 << 3)
#define CDAT_DSMAS_FLAG_HW_COHERENT (1 << 4)
#define CDAT_DSMAS_FLAG_DYNAMIC_CAP (1 << 5)
	uint16_t reserved;
	uint64_t DPA_base;
	uint64_t DPA_length;
} CDATDsmas;
_Static_assert(sizeof(CDATDsmas) == 24, "ERROR");

/* Device Scoped Latency and Bandwidth Information Structure - CDAT Table 5 */
typedef struct CDATDslbis {
	CDATSubHeader header;
	uint8_t handle;
	/* Definitions of these fields refer directly to HMAT fields */
	uint8_t flags;
	uint8_t data_type;
	uint8_t reserved;
	uint64_t entry_base_unit;
	uint16_t entry[3];
	uint16_t reserved2;
} CDATDslbis;
_Static_assert(sizeof(CDATDslbis) == 24, "ERROR");
