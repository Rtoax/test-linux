#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

int local_i = 123;
int local_i_no;
/* No rela entry */
static int s_local_i = 123;

#define P_int(i)	printk("I: %-16s  %-8d %016p.\n", #i, i, (void *)&i);
#define P_long(l)	printk("L: %-16s  %-8lx %016p.\n", #l, l, (void *)&l);
#define P_f(f)		printk("F: %-16s           %016p.\n", #f, (void *)f);

void print(void) {}

static int kernel_init(void)
{
	local_i++;
	local_i_no += 1;
	printk("\n");
	P_int(local_i);
	P_int(local_i_no);
	P_int(s_local_i);
	P_f(kernel_init);
	P_f(print);
	P_long(vmalloc_base);

	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
