#include <argp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pcie_helpers.h"

static char slot[64] = { 0 };
static char config[256] = "/sys/bus/pci/devices/0000:02:02.0/config";

const char argp_prog_doc[] = "PCIe configuration space";

static const struct argp_option opts[] = {
	{ "slot", 's', "SLOT", 0, "specify slot, like 0000:00:1f.6" },
	{ "config-file", 'f', "CONFIG-FILE", 0,
	  "config file name, like /sys/bus/pci/devices/0000:00:1f.6/config" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 's':
		strncpy(slot, arg, sizeof(slot));
		break;
	case 'f':
		strncpy(config, arg, sizeof(config));
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

int main(int argc, char *argv[])
{
	int err;
	FILE *fp;
	struct pci_cs_hdr_common common_header;
	struct pci_cs_hdr_type0 type0_header;
	struct pci_cs_hdr_type1 type1_header;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (strlen(slot) > 0) {
		/* TODO: maybe not 0000: */
		if (strncmp(slot, "0000:", 5)) {
			snprintf(config, sizeof(config),
				 "/sys/bus/pci/devices/0000:%s/config", slot);
		} else {
			snprintf(config, sizeof(config),
				 "/sys/bus/pci/devices/%s/config", slot);
		}
	}

	pci_cs_check_headers();

	fp = fopen(config, "r");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", config);
		exit(EXIT_FAILURE);
	}

	fread(&common_header, sizeof(common_header), 1, fp);
	rewind(fp);

	if ((common_header.header_type & 0x7f) == 0) {
		fread(&type0_header, sizeof(type0_header), 1, fp);
		pci_cs_print_type0(&type0_header);
	} else if ((common_header.header_type & 0x7f) == 1) {
		fread(&type1_header, sizeof(type1_header), 1, fp);
		pci_cs_print_type1(&type1_header);
	} else {
		pci_cs_print_common(&common_header);
		fprintf(stderr, "ERROR: Unknown header type %d(0x%x)\n",
			common_header.header_type, common_header.header_type);
		exit(EXIT_FAILURE);
	}

	fclose(fp);
	return 0;
}
