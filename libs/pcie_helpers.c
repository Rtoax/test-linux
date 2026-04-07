// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <stdio.h>
#include "pcie_helpers.h"

void print_pci_config_space_common(struct pci_config_space_common *c)
{
	printf("Vendor ID: 0x%x\n", c->vendor_id);
	printf("Device ID: 0x%x\n", c->device_id);
	printf("Command 0x%x\n", c->command);
	printf("Status: 0x%x\n", c->status);
	printf("Revison ID: %x\n", c->revision_id);
	printf("Class code (ProgIF): %x\n", c->prog_if);
	printf("Class code (SubClass): %x\n", c->subclass);
	printf("Class code (class_code): %x\n", c->class_code);
	printf("Cache Line: %x\n", c->cache_line_size);
	printf("Latency Timer: %x\n", c->latency_timer);
	printf("Header Type: %d\n", c->header_type);
	printf("Bist: %d\n", c->bist);
}

void print_pci_config_space_type0(struct pci_config_space_type0 *t)
{
	int i;

	if (t->common.header_type != 0) {
		fprintf(stderr,
			"WARNING: Not found pcie type0 header, skipping.\n");
		return;
	}

	print_pci_config_space_common((void *)t);

	for (i = 0; i < 6; i++)
		printf("Bar[%d] = 0x%x\n", i, t->bar[i]);

	printf("CardBus CIS Ptr: 0x%x\n", t->cardbus_cis_ptr);
	printf("SubSystem Vendor ID: %x\n", t->subsystem_vendor_id);
	printf("SubSystem ID: %x\n", t->subsystem_id);
	printf("Expansion ROM Base Addr: 0x%x\n", t->expansion_rom_base_addr);
	printf("Capabilities Pointer 0x%x\n", t->capabilities_pointer);
	printf("Interrypt Line: %x\n", t->interrupt_line);
	printf("Interrypt Pin: %x\n", t->interrupt_pin);
	printf("Min Gnt: %x\n", t->min_gnt);
	printf("Max Lat: %x\n", t->max_lat);
}
