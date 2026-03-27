#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/platform_device.h>

static struct platform_device *test_dev;

static int __init test_dev_init(void)
{
	int ret;

	test_dev = platform_device_alloc("test_firmware", -1);
	if (!test_dev) {
		pr_err("Failed to allocate platform device\n");
		return -ENOMEM;
	}

	ret = platform_device_add(test_dev);
	if (ret) {
		pr_err("Failed to add platform device: %d\n", ret);
		platform_device_put(test_dev);
		return ret;
	}

	pr_info("Test via device %s\n", dev_name(&test_dev->dev));

	platform_device_del(test_dev);
	platform_device_put(test_dev);
	return -EINVAL;
}

module_init(test_dev_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
