/*file: invalid_op.c */
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/kallsyms.h>

#include "invalid_opcode.h"

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
