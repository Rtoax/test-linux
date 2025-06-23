#pragma once
#include <stdint.h>

struct pci_config_space_type0 {
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	uint16_t status;
	uint8_t  revision_id;
	uint8_t  prog_if;
	uint8_t  subclass;
	uint8_t  class_code;
	uint8_t  cache_line_size;
	uint8_t  latency_timer;
	/* 0 - normal, 1 - bridge, 2 - cardbus */
	uint8_t  header_type;
	uint8_t  bist;
	uint32_t bar[6];
	uint32_t cardbus_cis_ptr;
	uint16_t subsystem_vendor_id;
	uint16_t subsystem_id;
	uint32_t expansion_rom_base_addr;
	uint8_t  capabilities_pointer;
	uint8_t  reserved1[7];
	uint8_t  interrupt_line;
	uint8_t  interrupt_pin;
	uint8_t  min_gnt;
	uint8_t  max_lat;
};
