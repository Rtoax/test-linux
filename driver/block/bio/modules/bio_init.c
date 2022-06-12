/**
 *	File	bio_init.c
 *	Time	2021.12.21
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bio.h>
#include <linux/slab.h>

struct bio test_bio;

static int kernel_init(void)
{
	struct bio_vec *vecs;
	int nr_pages = 32;

	printk(KERN_INFO "my bio test init.\n");
	
	vecs = kmalloc_array(nr_pages, sizeof(struct bio_vec), GFP_KERNEL);

	bio_init(&test_bio, vecs, nr_pages);

	return 0;
}

static void kernel_exit(void)
{
	bio_uninit(&test_bio);
	printk(KERN_INFO "my bio test exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
