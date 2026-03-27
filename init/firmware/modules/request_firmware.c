#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/firmware.h>

static int __init test_firmware_init(void)
{
	const struct firmware *fw;
	int ret;
	const char *bin = "test-firmware.bin";

	pr_info("Test firmware module: requesting '%s'\n", bin);
	ret = request_firmware(&fw, bin, NULL);
	if (ret) {
		pr_err("Failed to load firmware: %d\n", ret);
		return ret;
	}

	pr_info("Firmware loaded, size: %zu bytes\n", fw->size);
	release_firmware(fw);

	return -EINVAL;
}

module_init(test_firmware_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
