/*file: invalid_op.c */
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/kallsyms.h>

/* ud2 - undefined */
/* TODO: How to emulate 'invalid opcode' error */
#define INVALID_OP_BUG()       \
	__asm__ __volatile__(      \
		"ud2\n"                \
		"\t.word %c0\n"        \
		"\t.long %c1\n"        \
		: : "i" (__LINE__), "i" (__FILE__))

static int __init invalid_op_init(void)
{
	INVALID_OP_BUG();
	return 0;
}

static void invalid_op_exit(void)
{
	/* do nothing */
}

module_init(invalid_op_init);
module_exit(invalid_op_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("test invalid opcode");
