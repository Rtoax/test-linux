#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <capstone/platform.h>
#include <capstone/capstone.h>

void print_string_hex(FILE *fp, const char *comment, unsigned char *str,
		      size_t len)
{
	unsigned char *c;
	fprintf(fp, "%s", comment);
	for (c = str; c < str + len; c++)
		fprintf(fp, "0x%02x ", *c & 0xff);
	fprintf(fp, "\n");
}

int fdisasm(FILE *fp, cs_arch arch, cs_mode mode, unsigned char *code,
	    size_t size)
{
	uint64_t address = 0x1000;
	cs_insn *insn;
	size_t j, count;
	csh handle;
	int ret = 0;


	cs_err err = cs_open(arch, mode, &handle);
	if (err) {
		fprintf(stderr, "cs_open() fatal returned: %u\n", err);
		return -EINVAL;
	}

	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

	count = cs_disasm(handle, code, size, address, 0, &insn);
	if (!count) {
		fprintf(stderr, "ERROR: Failed to disasm given code!\n");
		ret = -EINVAL;
		goto close;
	}

	fprintf(fp, "Disasm:\n");
	for (j = 0; j < count; j++)
		fprintf(fp, "0x%" PRIx64 ":\t%s\t%s\n",
			insn[j].address,
			insn[j].mnemonic,
			insn[j].op_str);
	fprintf(fp, "0x%" PRIx64 ":\n", insn[j-1].address + insn[j-1].size);

	cs_free(insn, count);
close:
	cs_close(&handle);
	return ret;
}

int main(void)
{
#define X86_64_CODE \
	"\x55\x48\x8b\x05\xb8\x13\x00\x00\xe9\xea\xbe\xad\xde\xff\x25\x23\x01\x00\x00\xe8\xdf\xbe\xad\xde\x74\xff"

/* see kvm/playground/load-payload01-program.asm */
#define X86_32_CODE            \
	"\x66\xba\xf8\x03"     \
	"\xb8\x61\x62\x63\x64" \
	"\xe8\x01\x00\x00\x00" \
	"\xf4"                 \
	"\x52"                 \
	"\x51"                 \
	"\xb9\x04\x00\x00\x00" \
	"\x66\xba\xf8\x03"     \
	"\xee"                 \
	"\xc1\xe8\x08"         \
	"\x83\xe9\x01"         \
	"\x75\xf7"             \
	"\xb0\x78"             \
	"\xee"                 \
	"\x59"                 \
	"\x5a"                 \
	"\xc3"

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
	print_string_hex(stdout, "Code:", code, size);
	fdisasm(stdout, arch, mode, code, size);

	arch = CS_ARCH_X86;
	mode = CS_MODE_32;
	code = (unsigned char *)X86_32_CODE;
	size = sizeof(X86_32_CODE) - 1;
	print_string_hex(stdout, "Code:", code, size);
	fdisasm(stdout, arch, mode, code, size);

	arch = CS_ARCH_ARM64;
	mode = CS_MODE_ARM;
	code = (unsigned char *)AArch64_CODE;
	size = sizeof(AArch64_CODE) - 1;
	print_string_hex(stdout, "Code:", code, size);
	fdisasm(stdout, arch, mode, code, size);

	return 0;
}
