#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mlx5/device.h>

struct mlx5_ifc_mbox_in_bits {
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         reserved_at_40[0x40];
};

struct data {
	u16 opcode;
	u16 uid;
};

static int kernel_init(void)
{
	struct data in = {
		.opcode = 0x1122,
		.uid = 0x3344,
	};
	printk(KERN_INFO "%x\n", MLX5_GET(mbox_in, &in, uid));
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
