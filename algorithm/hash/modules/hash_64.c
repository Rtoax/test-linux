/**
 *	File	hash_64.c
 *	Time	2021.11.18
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>

static char *docs[] = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	NULL
};

static int kernel_init(void)
{
	int i = 0;
	char *s;
	unsigned int bits = 3;

    printk(KERN_INFO "my init.\n");
	
	while((s = docs[i++])) {
		printk("%d\n", hash_64((u64)s, bits));
	}
    return 0;
}

static void kernel_exit(void)
{
    printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
