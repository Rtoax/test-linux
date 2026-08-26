// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <stdint.h>

/**
 * PCI Express® Base Specification Revision 4.0 Version 0.3, 7.5.1. Type 0/1 Common Configuration Space
 */
struct pci_cs_hdr_common {
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	/**
	 * Status Bits
	 * 0: Immediate Readiness
	 * 1-2: Reserved
	 * 3: Interrupt Status
	 * 4: Capabilities List
	 * 5-7: Reserved
	 * 8: Master Data Parity Error
	 * 9-10: Reserved
	 * 11: Signaled Target Abort
	 * 12: Received Target Abort
	 * 13: Received Master Abort
	 * 14: Signaled System Error
	 * 15: Detected Parity Error
	 */
	uint16_t status;
	uint8_t revision_id;
	uint8_t prog_if;
	uint8_t subclass;
	uint8_t class_code;
	uint8_t cache_line_size;
	uint8_t latency_timer;
	/**
	 * 7 bit: Multi-Function Device or not
	 * 0-6 bits: 0 - normal, 1 - bridge, 2 - cardbus
	 */
	uint8_t header_type;
	uint8_t bist;
} __attribute__((packed));
_Static_assert(sizeof(struct pci_cs_hdr_common) == 16,
	       "Bad Type 0/1 Common Configuration Space size");

/**
 * PCI Express® Base Specification Revision 4.0 Version 0.3, 7.5.2. Type 0 Configuration Space Header
 */
struct pci_cs_hdr_type0 {
	struct pci_cs_hdr_common common;
	/* Base Address Register */
	uint32_t bar[6];
	uint32_t cardbus_cis_ptr;
	uint16_t subsystem_vendor_id;
	uint16_t subsystem_id;
	uint32_t expansion_rom_base_addr;
	uint8_t capabilities_pointer;
	uint8_t reserved1[7];
	uint8_t interrupt_line;
	uint8_t interrupt_pin;
	uint8_t min_gnt;
	uint8_t max_lat;
} __attribute__((packed));
_Static_assert(sizeof(struct pci_cs_hdr_type0) == 64,
	       "Bad Type 0 Configuration Space Header size");

/**
 * PCI Express® Base Specification Revision 4.0 Version 0.3, 7.5.3. Type 1 Configuration Space Header
 */
struct pci_cs_hdr_type1 {
	struct pci_cs_hdr_common common;
	/* Base Address Register */
	uint32_t bar[2];
	uint8_t primary_bus;
	uint8_t second_bus;
	uint8_t sub_bus;
	uint8_t snd_latency_timer;
	uint8_t io_base;
	uint8_t io_limit;
	uint16_t secondary_status;
	uint16_t mem_base;
	uint16_t mem_limit;
	uint16_t pref_mem_base;
	uint16_t pref_mem_limit;
	uint32_t pref_base_upper;
	uint32_t pref_limit_upper;
	uint16_t io_base_upper;
	uint16_t io_limit_upper;
	uint8_t cap_ptr;
	uint8_t reserved1[3];
	uint32_t rom_base_addr;
	uint8_t irq_line;
	uint8_t irq_pin;
	uint16_t bridge_control;
} __attribute__((packed));
_Static_assert(sizeof(struct pci_cs_hdr_type1) == 64,
	       "Bad Type 1 Configuration Space Header size");

/**
 * Configuration space
 */
void pci_cs_check_headers(void);
const char *pci_cs_type_name(uint8_t header_type, char *buf, size_t buf_sz);

void pci_cs_print_common(struct pci_cs_hdr_common *c);
void pci_cs_print_type0(struct pci_cs_hdr_type0 *t);
void pci_cs_print_type1(struct pci_cs_hdr_type1 *t);
