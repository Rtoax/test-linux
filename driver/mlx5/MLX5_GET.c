#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mlx5/device.h>

/* linux/drivers/net/ethernet/mellanox/mlx5/core/cmd.c */
struct mlx5_ifc_mbox_in_bits {
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         reserved_at_40[0x40];
};

struct data_bigendian {
	u16 opcode;
	u16 uid;
	u16 reserved_at_20;
	u16 op_mod;
	u64 reserved_at_40;
};

static int kernel_init(void)
{
	struct data_bigendian in = {
		.opcode = 0x1122,
		.uid = 0x3344,
		.op_mod = 0x5566,
	};
	printk(KERN_INFO "size of bits %ld vs original %ld\n",
		sizeof(struct mlx5_ifc_mbox_in_bits), sizeof(struct data_bigendian));
	printk(KERN_INFO "uid %x\n", MLX5_GET(mbox_in, &in, uid));
	printk(KERN_INFO "op_mod %x\n", MLX5_GET(mbox_in, &in, op_mod));
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
