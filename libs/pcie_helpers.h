// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <stdint.h>

struct pci_config_space_common {
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	uint16_t status;
	uint8_t revision_id;
	uint8_t prog_if;
	uint8_t subclass;
	uint8_t class_code;
	uint8_t cache_line_size;
	uint8_t latency_timer;
	/* 0 - normal, 1 - bridge, 2 - cardbus */
	uint8_t header_type;
	uint8_t bist;
} __attribute__((packed));

struct pci_config_space_type0 {
	struct pci_config_space_common common;
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

void print_pci_config_space_common(struct pci_config_space_common *c);
void print_pci_config_space_type0(struct pci_config_space_type0 *t);
