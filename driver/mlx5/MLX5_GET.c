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

struct real_mbox_in {
	u16 opcode;
	u16 uid;
	u16 reserved_at_20;
	u16 op_mod;
	u64 reserved_at_40;
};

struct mlx5_ifc_rongtao_bits {
	u8         data1[32];
	u8         data2[32];
	u8         data3[8];
};

struct real_rongtao {
	u32 data1;
	u32 data2;
	u8 data3;
};

static int kernel_init(void)
{
	struct real_mbox_in in = {
		.opcode = 0x1122,
		.uid = 0x3344,
		.op_mod = 0x5566,
	};

	printk(KERN_INFO "size of bits %ld vs original %ld\n",
		sizeof(struct mlx5_ifc_mbox_in_bits), sizeof(struct real_mbox_in));
	printk(KERN_INFO "uid %x, %ld, %ld\n", MLX5_GET(mbox_in, &in, uid),
		__mlx5_dw_off(mbox_in, uid), __mlx5_bit_off(mbox_in, uid));
	printk(KERN_INFO "op_mod %x\n", MLX5_GET(mbox_in, &in, op_mod));

	struct real_rongtao rongtao_in = {
		.data1 = 0x11223344,
		.data2 = 0x55667788,
		.data3 = 0xff,
	};

	printk(KERN_INFO "data2 %x\n", MLX5_GET(rongtao, &rongtao_in, data2));
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
