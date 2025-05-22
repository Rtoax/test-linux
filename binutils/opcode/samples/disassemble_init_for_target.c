#ifndef ARCH_aarch64
#define ARCH_aarch64
#endif
#include <stdio.h>
#include <stdarg.h>
#include <dis-asm.h>

int fprintf_custom(void *stream, const char *fmt, ...)
{
	char buffer[128];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	printf("%s", buffer);
	return 0;
}

int main(void)
{
	disassemble_info dinfo;
	disassembler_ftype disasm;

#ifdef INIT_DISASSEMBLE_INFO
	INIT_DISASSEMBLE_INFO(dinfo, stdout, fprintf_custom, NULL);
#else
	init_disassemble_info(&dinfo, stdout, fprintf_custom);
#endif

#if 0
	/* x86: "mov eax, 0x1234" */
	unsigned char code[] = {0xb8, 0x34, 0x12, 0x00, 0x00};
	/* arm: "mov r0, #0" */
	unsigned char code[] = {0x00, 0x00, 0xa0, 0xe3};
#endif
	/* aarch64: "mov x0, #0" */
	unsigned char code[] = {0x00, 0x00, 0x80, 0xd2};
	size_t code_len = sizeof(code);
	bfd_vma pc = 0;

	dinfo.arch = bfd_arch_aarch64;
	dinfo.mach = bfd_mach_aarch64;
	dinfo.buffer = code;
	dinfo.buffer_vma = 0;
	dinfo.buffer_length = code_len;
	dinfo.endian = BFD_ENDIAN_LITTLE;

	disassemble_init_for_target(&dinfo);

	disasm = disassembler(bfd_arch_aarch64, false, bfd_mach_aarch64, NULL);

	printf("disassemble: disasm = %p\n", disasm);
	while (code_len > 0) {
		int len = disasm(pc, &dinfo);
		if (len <= 0)
			break;

		pc += len;
		code_len -= len;
	}

	return 0;
}
