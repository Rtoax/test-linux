#pragma once

/* ud2 - undefined */
/* TODO: How to emulate 'invalid opcode' error */
#define INVALID_OP_BUG()       \
	__asm__ __volatile__(      \
		"ud2\n"                \
		"\t.word %c0\n"        \
		"\t.long %c1\n"        \
		: : "i" (__LINE__), "i" (__FILE__))

static inline __attribute__((unused)) int invalid_op_init(void)
{
	INVALID_OP_BUG();
	return 0;
}
