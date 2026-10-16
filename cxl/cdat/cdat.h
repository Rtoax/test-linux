// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * CXL CDAT (Coherent Device Attribute Table) Structure
 *
 * Refs:
 * - https://git.zx2c4.com/qemu/plain/include/hw/cxl/cxl_cdat.h
 * - https://docs.kernel.org/driver-api/cxl/platform/cdat.html
 * - UEFI Specification Release 2.10
 *   11.12.6 Coherent Device Attribute Table (CDAT) Type
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

/**
 * Device Scoped Memory Affinity Structure - CDAT Table 3
 *
 * The DSMAS contains information such as DSMADHandle, the DPA Base, and DPA
 * Length.
 *
 * This table is used by Linux in conjunction with the Device Scoped Latency
 * and Bandwidth Information Structure (DSLBIS) to determine the performance
 * attributes of the CXL device itself.
 */
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

/**
 * Device Scoped Latency and Bandwidth Information Structure - CDAT Table 5
 *
 * This table is used by Linux in conjunction with DSMAS to determine the
 * performance attributes of a CXL device. The DSLBIS contains latency and
 * bandwidth information based on DSMADHandle matching.
 */
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

/* Device Scoped EFI Memory Type Structure - CDAT Table 8 */
typedef struct CDATDsemts {
	CDATSubHeader header;
	uint8_t DSMAS_handle;
	uint8_t EFI_memory_type_attr;
	uint16_t reserved;
	uint64_t DPA_offset;
	uint64_t DPA_length;
} CDATDsemts;
_Static_assert(sizeof(CDATDsemts) == 24, "ERROR");

/* Switch Scoped Latency and Bandwidth Information Structure - CDAT Table 9 */
typedef struct CDATSslbisHeader {
	CDATSubHeader header;
	uint8_t data_type;
	uint8_t reserved[3];
	uint64_t entry_base_unit;
} CDATSslbisHeader;
_Static_assert(sizeof(CDATSslbisHeader) == 16, "ERROR");

#define CDAT_PORT_ID_USP 0x100
/* Switch Scoped Latency and Bandwidth Entry - CDAT Table 10 */
typedef struct CDATSslbe {
	uint16_t port_x_id;
	uint16_t port_y_id;
	uint16_t latency_bandwidth;
	uint16_t reserved;
} CDATSslbe;
_Static_assert(sizeof(CDATSslbe) == 8, "ERROR");

/**
 * The SSLBIS contains information about the latency and bandwidth of a switch.
 *
 * The table is used by Linux to compute the performance coordinates of a CXL
 * path from the device to the root port where a switch is part of the path.
 */
typedef struct CDATSslbis {
	CDATSslbisHeader sslbis_header;
	CDATSslbe sslbe[];
} CDATSslbis;
