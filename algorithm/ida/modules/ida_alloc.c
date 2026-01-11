#include <linux/module.h>
#include <linux/idr.h>
#include <linux/kernel.h>

static DEFINE_IDA(test_ida);

static int test_init(void)
{
	int i, id;
	struct ida *ida = &test_ida;

	if(ida_is_empty(ida)) {
		printk("empty.\n");
	}

	for (i = 0; i < 10000; i+=1) {
		if((id = ida_alloc(ida, GFP_KERNEL)) != i)
			printk("%d <-> %d\n", i, id);
	}
	ida_free(ida, 20);
	ida_free(ida, 21);

	for (i = 0; i < 3; i++) {
		id = ida_alloc(ida, GFP_KERNEL);
		printk("%d <-> %d\n", i, id);
	}
	for (i = 0; i < 5000; i++)
		ida_free(ida, i);
	
	ida_destroy(ida);

	return 0;
}

static void test_exit(void)
{
	
}

module_init(test_init);
module_exit(test_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
