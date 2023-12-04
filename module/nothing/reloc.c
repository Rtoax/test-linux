#include <linux/module.h>

int global_int1;
int global_int2;
int global_int3 = 0xabcdffff;
static int sglobal_int1;

void func1(void) {}
static void sfunc1(void) {}

MODULE_LICENSE("Dual BSD/GPL");
