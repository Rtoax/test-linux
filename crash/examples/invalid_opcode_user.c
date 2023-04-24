#include "invalid_opcode.h"

static int invalid_op_init(void)
{
	INVALID_OP_BUG();
	return 0;
}

int main(int argc, char *argv[])
{
	return invalid_op_init();
}
