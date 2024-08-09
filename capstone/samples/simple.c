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

int disasm(cs_arch arch, cs_mode mode, unsigned char *code, size_t size)
{
	uint64_t address = 0x1000;
	cs_insn *insn;
	size_t count;
	csh handle;

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

int main(void)
{
#define X86_64_CODE \
	"\x55\x48\x8b\x05\xb8\x13\x00\x00\xe9\xea\xbe\xad\xde\xff\x25\x23\x01\x00\x00\xe8\xdf\xbe\xad\xde\x74\xff"

#define AArch64_CODE \
	"\x09\x00\x38\xd5" \
	"\xbf\x40\x00\xd5" \
	"\x0c\x05\x13\xd5" \
	"\x20\x50\x02\x0e" \
	"\x20\xe4\x3d\x0f" \
	"\x00\x18\xa0\x5f" \
	"\xa2\x00\xae\x9e" \
	"\x9f\x37\x03\xd5" \
	"\xbf\x33\x03\xd5" \
	"\xdf\x3f\x03\xd5" \
	"\x21\x7c\x02\x9b" \
	"\x21\x7c\x00\x53" \
	"\x00\x40\x21\x4b" \
	"\xe1\x0b\x40\xb9" \
	"\x20\x04\x81\xda" \
	"\x20\x08\x02\x8b" \
	"\x10\x5b\xe8\x3c" \
	"\xfd\x7b\xba\xa9" \
	"\xfd\xc7\x43\xf8"

	cs_arch arch;
	cs_mode mode;
	unsigned char *code;
	size_t size;

	arch = CS_ARCH_X86;
	mode = CS_MODE_64;
	code = (unsigned char *)X86_64_CODE;
	size = sizeof(X86_64_CODE) - 1;
	disasm(arch, mode, code, size);

	arch = CS_ARCH_ARM64;
	mode = CS_MODE_ARM;
	code = (unsigned char *)AArch64_CODE;
	size = sizeof(AArch64_CODE) - 1;
	disasm(arch, mode, code, size);

	return 0;
}
