#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/firmware.h>
#include <linux/platform_device.h>

static struct platform_device *test_dev;

static int __init test_firmware_init(void)
{
	const struct firmware *fw;
	int ret;
	/**
	 * Don't forget create /lib/firmware/test-firmware.bin dummy file.
	 */
	const char *bin = "test-firmware.bin";

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

	pr_info("Test firmware module: requesting '%s' via device %s\n", bin,
		dev_name(&test_dev->dev));
	ret = request_firmware(&fw, bin, NULL);
	if (ret) {
		pr_err("Failed to load firmware: %d\n", ret);
		goto release_dev;
	}

	/* Use firmware */
	for (int i; i < fw->size; i++) {
		pr_info("fw[%d] = 0x%x\n", i, *(u8 *)(fw->data + i));
	}

	pr_info("Firmware loaded, size: %zu bytes\n", fw->size);
	release_firmware(fw);
release_dev:
	platform_device_del(test_dev);
	platform_device_put(test_dev);
	return -EINVAL;
}

module_init(test_firmware_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
