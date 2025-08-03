#include <linux/kernel.h>

#include "foo.h"

void foo(void)
{
	printk(KERN_INFO "Hi from Foo\n");
}
