#include <argp.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <pci/header.h>
#include "pcie_helpers.h"

#ifndef offsetof
#define offsetof(type, number) __builtin_offsetof(type, number)
#endif

static char *config = "/sys/bus/pci/devices/0000:02:02.0/config";

const char argp_prog_doc[] = "PCIe configuration space";

static const struct argp_option opts[] = {
	{ "config-file", 'f', "CONFIG FILE", 0,
	  "config file name, like /sys/bus/pci/devices/0000:00:1f.6/config" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'f':
		config = arg;
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

static void check_type0_header(void)
{
#define CHK(field, off)	\
	assert(offsetof(struct pci_config_space_type0, field) == off);

	CHK(common.vendor_id, PCI_VENDOR_ID);
	CHK(common.device_id, PCI_DEVICE_ID);
	CHK(common.command, PCI_COMMAND);
	CHK(common.status, PCI_STATUS);
	CHK(common.revision_id, PCI_REVISION_ID);
	CHK(common.prog_if, PCI_CLASS_PROG);
	CHK(common.subclass, PCI_CLASS_DEVICE);
	CHK(common.cache_line_size, PCI_CACHE_LINE_SIZE);
	CHK(common.latency_timer, PCI_LATENCY_TIMER);
	CHK(common.header_type, PCI_HEADER_TYPE);
	CHK(common.bist, PCI_BIST);
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

int main(int argc, char *argv[])
{
	int err;
	FILE *fp;
	struct pci_config_space_common common_header;
	struct pci_config_space_type0 type0_header;
	struct pci_config_space_type1 type1_header;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	check_type0_header();

	fp = fopen(config, "r");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", config);
		exit(EXIT_FAILURE);
	}

	fread(&common_header, sizeof(common_header), 1, fp);
	rewind(fp);

	if ((common_header.header_type & 0x7f) == 0) {
		fread(&type0_header, sizeof(type0_header), 1, fp);
		print_pci_config_space_type0(&type0_header);
	} else if ((common_header.header_type & 0x7f) == 1) {
		fread(&type1_header, sizeof(type1_header), 1, fp);
		print_pci_config_space_type1(&type1_header);
	} else {
		print_pci_config_space_common(&common_header);
		fprintf(stderr, "ERROR: Unknown header type %d(0x%x)\n",
			common_header.header_type, common_header.header_type);
		exit(EXIT_FAILURE);
	}

	fclose(fp);

	return 0;
}
