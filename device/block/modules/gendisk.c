#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/device.h>

static int __init traverse_gendisks_init(void)
{
#if 0 // TODO: block_class is not exported
	struct class *blk_class = &block_class;
	struct device *dev;
	struct class_dev_iter iter;
	struct gendisk *disk;

	if (!blk_class) {
		pr_err("Block class not initialized\n");
		return -ENODEV;
	}

	mutex_lock(&block_class_lock);
	class_dev_iter_init(&iter, blk_class, NULL, NULL);

	while ((dev = class_dev_iter_next(&iter))) {
		disk = dev_to_disk(dev);
		if (disk) {
			pr_info("Disk: %s, major=%d, minors=%d-%d\n",
				disk->disk_name,
				MAJOR(disk->major),
				disk->first_minor,
				disk->first_minor + disk->minors - 1);
		}
	}

	class_dev_iter_exit(&iter);
	mutex_unlock(&block_class_lock);
#endif
	return -EINVAL;
}

module_init(traverse_gendisks_init);
MODULE_LICENSE("GPL");
