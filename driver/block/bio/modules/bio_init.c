#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bio.h>
#include <linux/slab.h>
#include <linux/version.h>


struct bio test_bio;

static int kernel_init(void)
{
	struct bio_vec *vecs;
	int nr_pages = 32;

	printk(KERN_INFO "my bio test init.\n");
	
	vecs = kmalloc_array(nr_pages, sizeof(struct bio_vec), GFP_KERNEL);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 17, 0)
	bio_init(&test_bio, vecs, nr_pages);
#else
	/* TODO */
#endif

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
