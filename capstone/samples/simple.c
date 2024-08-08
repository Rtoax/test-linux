#include <stdio.h>
#include <stdlib.h>

#include <capstone/platform.h>
#include <capstone/capstone.h>

static void print_string_hex(const char *comment, unsigned char *str, size_t len)
{
	unsigned char *c;
	printf("%s", comment);
	for (c = str; c < str + len; c++)
		printf("0x%02x ", *c & 0xff);
	printf("\n");
}

int main(void)
{
#define X86_CODE64 "\x55\x48\x8b\x05\xb8\x13\x00\x00\xe9\xea\xbe\xad\xde\xff\x25\x23\x01\x00\x00\xe8\xdf\xbe\xad\xde\x74\xff"
	cs_arch arch;
	cs_mode mode;
	unsigned char *code;
	size_t size;

	uint64_t address = 0x1000;
	cs_insn *insn;
	size_t count;
	csh handle;

	arch = CS_ARCH_X86;
	mode = CS_MODE_64;
	code = (unsigned char *)X86_CODE64;
	size = sizeof(X86_CODE64) - 1;

	cs_err err = cs_open(arch, mode, &handle);
	if (err) {
		printf("Failed on cs_open() with error returned: %u\n", err);
		abort();
	}

	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

	print_string_hex("Code:", code, size);

	count = cs_disasm(handle, code, size, address, 0, &insn);
	if (count) {
		size_t j;

		printf("Disasm:\n");
		for (j = 0; j < count; j++)
			printf("0x%" PRIx64 ":\t%s\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
		printf("0x%" PRIx64 ":\n", insn[j-1].address + insn[j-1].size);

		cs_free(insn, count);
	} else {
		printf("ERROR: Failed to disasm given code!\n");
		abort();
	}

	cs_close(&handle);

	return 0;
}

