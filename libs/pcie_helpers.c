// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <pci/header.h>
#include "pcie_helpers.h"

#ifndef offsetof
#define offsetof(type, number) __builtin_offsetof(type, number)
#endif

void pci_cs_check_headers(void)
{
#define CHK(field, off) \
	assert(offsetof(struct pci_cs_hdr_common, field) == off);
	CHK(vendor_id, PCI_VENDOR_ID);
	CHK(device_id, PCI_DEVICE_ID);
	CHK(command, PCI_COMMAND);
	CHK(status, PCI_STATUS);
	CHK(revision_id, PCI_REVISION_ID);
	CHK(prog_if, PCI_CLASS_PROG);
	CHK(subclass, PCI_CLASS_DEVICE);
	CHK(cache_line_size, PCI_CACHE_LINE_SIZE);
	CHK(latency_timer, PCI_LATENCY_TIMER);
	CHK(header_type, PCI_HEADER_TYPE);
	CHK(bist, PCI_BIST);
#undef CHK
#define CHK(field, off) assert(offsetof(struct pci_cs_hdr_type0, field) == off);
	CHK(bar, PCI_BASE_ADDRESS_0);
	CHK(cardbus_cis_ptr, PCI_CARDBUS_CIS);
	CHK(subsystem_vendor_id, PCI_SUBSYSTEM_VENDOR_ID);
	CHK(subsystem_id, PCI_SUBSYSTEM_ID);
	CHK(expansion_rom_base_addr, PCI_ROM_ADDRESS);
	CHK(capabilities_pointer, PCI_CAPABILITY_LIST);
	CHK(interrupt_line, PCI_INTERRUPT_LINE);
	CHK(interrupt_pin, PCI_INTERRUPT_PIN);
	CHK(min_gnt, PCI_MIN_GNT);
	CHK(max_lat, PCI_MAX_LAT);
#undef CHK
#define CHK(field, off) assert(offsetof(struct pci_cs_hdr_type1, field) == off);
	CHK(primary_bus, PCI_PRIMARY_BUS);
	CHK(second_bus, PCI_SECONDARY_BUS);
	CHK(sub_bus, PCI_SUBORDINATE_BUS);
	CHK(snd_latency_timer, PCI_SEC_LATENCY_TIMER);
	CHK(io_base, PCI_IO_BASE);
	CHK(io_limit, PCI_IO_LIMIT);
	CHK(secondary_status, PCI_SEC_STATUS);
	CHK(mem_base, PCI_MEMORY_BASE);
	CHK(mem_limit, PCI_MEMORY_LIMIT);
	CHK(pref_mem_base, PCI_PREF_MEMORY_BASE);
	CHK(pref_mem_limit, PCI_PREF_MEMORY_LIMIT);
	CHK(pref_base_upper, PCI_PREF_BASE_UPPER32);
	CHK(pref_limit_upper, PCI_PREF_LIMIT_UPPER32);
	CHK(io_base_upper, PCI_IO_BASE_UPPER16);
	CHK(io_limit_upper, PCI_IO_LIMIT_UPPER16);
	CHK(rom_base_addr, PCI_ROM_ADDRESS1);
	CHK(bridge_control, PCI_BRIDGE_CONTROL);
#undef CHK
}

const char *pci_cs_type_name(uint8_t header_type, char *buf, size_t buf_sz)
{
	char *name = "Unknown";
	switch (header_type & 0x7f) {
	case 0:
		name = "Ordinary Device";
		break;
	case 1:
		name = "Bridge";
		break;
	case 2:
		name = "CardBus";
		break;
	}

	snprintf(buf, buf_sz, "%s%s", name,
		 header_type & 0x80 ? "" : " (Multi-Function Device)");
	return buf;
}

void pci_cs_print_common(struct pci_cs_hdr_common *c)
{
	char buf[64];
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
	printf("Header Type: %s\n",
	       pci_cs_type_name(c->header_type, buf, sizeof(buf)));
	printf("Bist: %d\n", c->bist);
}

void pci_cs_print_type0(struct pci_cs_hdr_type0 *t)
{
	int i;

	if ((t->common.header_type & 0x7f) != 0) {
		fprintf(stderr,
			"WARNING: Not found pcie type0 header, skipping.\n");
		return;
	}

	pci_cs_print_common((void *)t);

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

void pci_cs_print_type1(struct pci_cs_hdr_type1 *t)
{
	int i;

	if ((t->common.header_type & 0x7f) != 1) {
		fprintf(stderr,
			"WARNING: Not found pcie type0 header, skipping.\n");
		return;
	}

	pci_cs_print_common((void *)t);

	for (i = 0; i < 2; i++)
		printf("Bar[%d] = 0x%x\n", i, t->bar[i]);

	printf("Primary Bus: %x\n", t->primary_bus);
	printf("Second Bus: %x\n", t->second_bus);
	printf("Sub Bus: %x\n", t->sub_bus);
	printf("Second Latency Timer: %x\n", t->snd_latency_timer);
	printf("IO Base: %x\n", t->io_base);
	printf("IO Limit: %x\n", t->io_limit);
	printf("Secondary Status: %x\n", t->secondary_status);
	printf("Memory Base: %x\n", t->mem_base);
	printf("Memory Limit: %x\n", t->mem_limit);
	printf("Prefetchable Memory Base: %x\n", t->pref_mem_base);
	printf("Prefetchable Memory Limit: %x\n", t->pref_mem_limit);
	printf("Prefetchable Base Upper: %x\n", t->pref_base_upper);
	printf("Prefetchable Limit Upper: %x\n", t->pref_limit_upper);
	printf("IO Base Upper: %x\n", t->io_base_upper);
	printf("IO Limit Upper: %x\n", t->io_limit_upper);
	printf("Capabilities Pointer: %x\n", t->cap_ptr);
	printf("Expansion ROM Base Address: %x\n", t->rom_base_addr);
	printf("Interrupt Line: %x\n", t->irq_line);
	printf("Interrupt Pin: %x\n", t->irq_pin);
	printf("Bridge Control: %x\n", t->bridge_control);
}
