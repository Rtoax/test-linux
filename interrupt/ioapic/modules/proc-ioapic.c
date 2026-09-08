/*
 * Copyright 2016 Nikita Edward Baruzdin <nebaruzdin@gmail.com>
 *
 * The module creates pseudo-files /proc/ioapic0 and (optionally) /proc/ioapic1
 * that show the contents of the IO-APIC(s) registers, in particular
 * Redirection Table entries.
 *
 * The format of Redirection Table entries is described in the Intel datasheet
 * "82093AA I/O Advanced Programmable Interrupt Controller (IOAPIC)".
 *
 * Orginal repo: https://github.com/nebaruzdin/interrupt-modules
 * Modify by Rong Tao
 * 2021.12.04
 * - support linux-5.6+
 */

#include <linux/module.h>     // init_module(), printk()
#include <linux/proc_fs.h>    // proc_create(), remove_proc_entry()
#include <linux/seq_file.h>   // seq_printf(), seq_read(), seq_lseek()
#include <linux/version.h>    //
#include <linux/stat.h>       // file permissions
#include <asm/io.h>           // ioremap(), iounmap()


MODULE_DESCRIPTION("IO-APIC Redirection Table viewer.");
MODULE_AUTHOR("Nikita Edward Baruzdin <nebaruzdin@gmail.com>");
MODULE_LICENSE("GPL");

#define mod_info(fmt, ...) \
	printk(KERN_INFO "%s: " fmt, MODNAME, ##__VA_ARGS__)
#define mod_err(fmt, ...) \
	printk(KERN_ERR "%s: " fmt, MODNAME, ##__VA_ARGS__)

#define MODNAME                            "ioapic"
#define IOAPIC0_PROC_FILENAME              "ioapic0"
#define IOAPIC1_PROC_FILENAME              "ioapic1"

#define IOAPIC_REG_ID                      0x00
#define IOAPIC_REG_VER                     0x01
#define IOAPIC_REG_ARB                     0x02

#define IOAPIC_REG_ID_SHIFT_ID             24
#define IOAPIC_REG_ID_MASK_ID              0x0F000000
#define IOAPIC_REG_VER_SHIFT_VER           0
#define IOAPIC_REG_VER_MASK_VER            0x000000FF
#define IOAPIC_REG_VER_SHIFT_MAX_ENTRIES   16
#define IOAPIC_REG_VER_MASK_MAX_ENTRIES    0x00FF0000

static unsigned long ioapic0_base = 0xFEC00000;
module_param(ioapic0_base, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(ioapic0_base, "Base address for the primary IO-APIC, 0xFEC00000 by default.");

static unsigned long ioapic1_base = 0;
module_param(ioapic1_base, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(ioapic1_base, "Base address for the secondary IO-APIC, not used by default.");

struct ioapic {           // Offset:
	uint8_t  index;   // 0x00
	uint8_t  __pad0[15];
	uint32_t data;    // 0x10
	uint32_t __pad1[11];
	uint32_t eoi;     // 0x40
};

void __iomem *ioapic_addr;
uint32_t id;
uint32_t version;
uint32_t max_entries;


static inline uint32_t ioapic_read(void *ioapic_addr, const uint8_t reg)
{
	volatile struct ioapic *ioapic = ioapic_addr;

	ioapic->index = reg;
	return ioapic->data;
}

static inline void ioapic_write(void *ioapic_addr, const uint8_t reg,
                                const uint32_t value)
{
	volatile struct ioapic *ioapic = ioapic_addr;

	ioapic->index = reg;
	ioapic->data  = value;
}

static int ioapic_setup(uint32_t ioapic_base)
{
	uint32_t reg_id;
	uint32_t reg_ver;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
	ioapic_addr = ioremap_cache(ioapic_base, PAGE_SIZE);
#else
	ioapic_addr = ioremap_nocache(ioapic_base, PAGE_SIZE);
#endif

	reg_id  = ioapic_read(ioapic_addr, IOAPIC_REG_ID);
	reg_ver = ioapic_read(ioapic_addr, IOAPIC_REG_VER);

	// Check if IO-APIC is really there.
	if (reg_id & ~IOAPIC_REG_ID_MASK_ID) {
		mod_err("Bad data in IO-APIC ID register: %X. "
		        "Probably wrong IO-APIC base address.", reg_id);
		return -ENODEV;
	}
	if (reg_ver & ~IOAPIC_REG_VER_MASK_VER
	            & ~IOAPIC_REG_VER_MASK_MAX_ENTRIES) {
	        mod_err("Bad data in IO-APIC VER register: %X. "
	                "Probably wrong IO-APIC base address.", reg_ver);
	        return -ENODEV;
	}

	id          = (reg_id & IOAPIC_REG_ID_MASK_ID)
	              >> IOAPIC_REG_ID_SHIFT_ID;
	version     = (reg_ver & IOAPIC_REG_VER_MASK_VER)
	              >> IOAPIC_REG_VER_SHIFT_VER;
	max_entries = (reg_ver & IOAPIC_REG_VER_MASK_MAX_ENTRIES)
	              >> IOAPIC_REG_VER_SHIFT_MAX_ENTRIES;

	return 0;
}

static int ioapic_show(struct seq_file *sf, void *v)
{
	int pin;

	seq_printf(sf, "\nIO-APIC    ID %X    Version: %02X    "
	               "Max entries: %d\n",
	               id, version, max_entries + 1);

	for (pin = 0; pin <= max_entries; pin++) {
		uint32_t word_lo = ioapic_read(ioapic_addr, 0x10 + 2 * pin);
		uint32_t word_hi = ioapic_read(ioapic_addr, 0x11 + 2 * pin);
		if (pin % 3 == 0)
			seq_printf(sf, "\n");
		else
			seq_printf(sf, "    ");
		seq_printf(sf, "%03d: %08X%08X", pin, word_hi, word_lo);
	}
	seq_printf(sf, "\n\n");

	iounmap(ioapic_addr);
	return 0;
}

static int ioapic0_open(struct inode *inode, struct file *file)
{
	ioapic_setup(ioapic0_base);
	return single_open(file, ioapic_show, NULL);
}

static int ioapic1_open(struct inode *inode, struct file *file)
{
	ioapic_setup(ioapic1_base);
	return single_open(file, ioapic_show, NULL);
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static const struct proc_ops ioapic0_fops = {
	.proc_open    = ioapic0_open,
	.proc_read    = seq_read,
	.proc_lseek  = seq_lseek,
	.proc_release = single_release,
};

static const struct proc_ops ioapic1_fops = {
	.proc_open    = ioapic1_open,
	.proc_read    = seq_read,
	.proc_lseek  = seq_lseek,
	.proc_release = single_release,
};
#else
static const struct file_operations ioapic0_fops = {
	.owner   = THIS_MODULE,
	.open    = ioapic0_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static const struct file_operations ioapic1_fops = {
	.owner   = THIS_MODULE,
	.open    = ioapic1_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};
#endif

static int __init ioapic_init(void)
{
	int ret;

	mod_info("Loading.");

	// Check the presence of the IO-APICs before creating proc files.
	ret = ioapic_setup(ioapic0_base);
	if (ret < 0)
		return ret;
	if (ioapic1_base) {
		mod_info("ioapic1_base: %lX.", ioapic1_base);
		ret = ioapic_setup(ioapic1_base);
		if (ret < 0)
			return ret;
	}

	proc_create(IOAPIC0_PROC_FILENAME, 0, NULL, &ioapic0_fops);
	if (ioapic1_base)
		proc_create(IOAPIC1_PROC_FILENAME, 0, NULL, &ioapic1_fops);

	return 0;
}

static void __exit ioapic_exit(void)
{
	mod_info("Unloading.");

	remove_proc_entry(IOAPIC0_PROC_FILENAME, NULL);
	if (ioapic1_base)
		remove_proc_entry(IOAPIC1_PROC_FILENAME, NULL);
}

module_init(ioapic_init);
module_exit(ioapic_exit);
