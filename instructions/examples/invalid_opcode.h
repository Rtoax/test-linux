#pragma once

#if defined(__x86_64__)
/* ud2 - undefined */
/* TODO: How to emulate 'invalid opcode' error */
#define INVALID_OP_BUG()       \
	__asm__ __volatile__(      \
		"ud2\n"                \
		"\t.word %c0\n"        \
		"\t.long %c1\n"        \
		: : "i" (__LINE__), "i" (__FILE__))
#elif defined(__aarch64__)
/**
 * udf - It appears in the ARMv8 Architecture Reference Manual on page C6-1380.
 * It takes an immediate operand which can be any 16-bit value and is ignored,
 * e.g. udf #0xdead.
 *
 * The GNU assembler added support for the udf mnemonic fairly recently (I
 * believe in version 2.35, released July 2020), so if you have an older
 * version, it may not be supported. However, the encoding of udf #0 is
 * conveniently 0x00000000, so you can just write .inst 0 instead, or define
 * a macro if you plan to use it a lot.
 *
 * In fact, any instruction whose high 16 bits are 0 is a guaranteed udf, and
 * the low 16 bits are the immediate value. You could use different ones to
 * mark different parts of your code, for easy spotting in a memory dump. So
 * you can also do .inst 0x0000dead if you want.
 */
#define INVALID_OP_BUG()	\
	__asm__ __volatile__("udf #0");
#endif

static inline __attribute__((unused)) int invalid_op_init(void)
{
	INVALID_OP_BUG();
	return 0;
}
