#include <stdio.h>
#include <pci/header.h>
#include "header.h"

#ifndef offsetof
#define offsetof(type, number) __builtin_offsetof(type, number)
#endif
#include <assert.h>

static void check_header(void)
{
#define CHK(field, off)	\
	assert(offsetof(struct pci_config_space_type0, field) == off);

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
}

int main(void)
{
	check_header();
	return 0;
}
