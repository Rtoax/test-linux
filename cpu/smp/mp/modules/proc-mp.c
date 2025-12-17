/*
 * Copyright 2016 Nikita Edward Baruzdin <nebaruzdin@gmail.com>
 *
 * The module creates a pseudo-file /proc/mp that shows the contents of the
 * following three data structures:
 *   - MP Floating Pointer structure
 *   - MP Configuration Table Header
 *   - Base MP Configuration Table
 *
 * Their format is described in the "Intel Multiprocessor Specification
 * (version 1.4)".
 */

#include <linux/module.h>     // init_module(), printk()
#include <linux/proc_fs.h>    // proc_create(), remove_proc_entry()
#include <linux/seq_file.h>   // seq_printf(), seq_read(), seq_lseek()
#include <linux/version.h>    //
#include <asm/io.h>           // phys_to_virt(), virt_to_phys()


MODULE_DESCRIPTION("MP Configuration Table viewer.");
MODULE_AUTHOR("Nikita Edward Baruzdin <nebaruzdin@gmail.com>");
MODULE_LICENSE("GPL");

#define mod_info(fmt, ...) \
	printk(KERN_INFO "%s: " fmt, MODNAME, ##__VA_ARGS__)
#define mod_err(fmt, ...) \
	printk(KERN_ERR "%s: " fmt, MODNAME, ##__VA_ARGS__)

#define MODNAME                      "mp"
#define MP_PROC_FILENAME             "mp"

#define MPFP_SIGNATURE               0x5f504d5f   // "_MP_"
#define MPCT_SIGNATURE               0x504d4350   // "PCMP"

#define MPFP_SIGNATURE_BYTES         4
#define MPCT_SIGNATURE_BYTES         4

#define MPCT_ENTRY_TYPE_PROCESSOR    0
#define MPCT_ENTRY_BYTES_PROCESSOR   20
#define MPCT_ENTRY_BYTES_DEFAULT     8

#define MPFP_STRUCTURE_BYTES         16   // MP Floating Pointer Structure size
#define MPCT_HEADER_BYTES            44   // MP Configuration Table Header size

uint16_t base_mpct_bytes;   // Base Configuration Table size
uint8_t  *mpfp;             // MP Floating Pointer address
uint8_t  *mpct;             // MP Configuration Table address


static int mp_setup(void)
{
	phys_addr_t phys_addr;

	// Search for the MP Floating Pointer Structure signature in the
	// BIOS ROM.
	for (phys_addr = 0xF0000; phys_addr <= 0xFFFFF; phys_addr += 16) {
		mpfp = (uint8_t *)phys_to_virt(phys_addr);
		if (*(uint32_t *)mpfp == MPFP_SIGNATURE)
			break;
	}
	if (phys_addr == 0x100000) {
		mod_err("MP Floating Pointer Structure wasn't found.");
		return -ENODEV;
	}
	mod_info("MP Floating Pointer Structure "
	         "physical address: %pap \n", &phys_addr);

	// Read the address of the MP Configuration Table and confirm its
	// presence by checking the signature.
	phys_addr = (*(uint32_t *)(mpfp + MPFP_SIGNATURE_BYTES));
	mpct = (uint8_t *)phys_to_virt(phys_addr);
	if (*(uint32_t *)mpct != MPCT_SIGNATURE) {
		mod_err("MP Configuration Table signature doesn't match \"PCMP\" string.");
		return -ENODEV;
	}
	mod_info("MP Configuration Table Header "
	         "physical address: %pap \n", &phys_addr);

	// Get the size of the Base MP Configuration Table.
	base_mpct_bytes = *(uint32_t *)(mpct + MPCT_SIGNATURE_BYTES);
	mod_info("Base MP Configuration Table size: %d bytes\n", base_mpct_bytes);

	return 0;
}

static int mp_show(struct seq_file *sf, void *v)
{
	int pos;

	seq_printf(sf, "\nMP Floating Pointer Structure:\n");
	for (pos = 0; pos < MPFP_STRUCTURE_BYTES; pos++) {
		if (!(pos % 4))
			seq_printf(sf, "\n0x%03X:", pos);
		seq_printf(sf, " %02X", mpfp[pos]);
	}
	seq_printf(sf, "\n");

	seq_printf(sf, "\nMP Configuration Table Header:\n");
	for (pos = 0; pos < MPCT_HEADER_BYTES; pos++) {
		if (!(pos % 4))
			seq_printf(sf, "\n0x%03X:", pos);
		seq_printf(sf, " %02X", mpct[pos]);
	}
	seq_printf(sf, "\n");

	seq_printf(sf, "\nBase MP Configuration Table:\n");
	for (pos = MPCT_HEADER_BYTES; pos < base_mpct_bytes; ) {
		int entry_bytes;
		int byte;
		seq_printf(sf, "\n0x%03X:", pos);
		entry_bytes = (mpct[pos] == MPCT_ENTRY_TYPE_PROCESSOR) ?
		              MPCT_ENTRY_BYTES_PROCESSOR :
		              MPCT_ENTRY_BYTES_DEFAULT;
		for (byte = 0; byte < entry_bytes; byte++)
			seq_printf(sf, " %02X", mpct[pos + byte]);
		pos += entry_bytes;
	}
	seq_printf(sf, "\n");

	return 0;
}

static int mp_open(struct inode *inode, struct file *file)
{
	return single_open(file, mp_show, NULL);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static const struct proc_ops mp_fops = {
	.proc_open    = mp_open,
	.proc_read    = seq_read,
	.proc_lseek  = seq_lseek,
	.proc_release = single_release,
};
#else
static const struct file_operations mp_fops = {
	.owner   = THIS_MODULE,
	.open    = mp_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};
#endif
static int __init mp_init(void)
{
	int ret;

	mod_info("Loading.");

	ret = mp_setup();
	if (ret < 0)
		return ret;
	proc_create(MP_PROC_FILENAME, 0, NULL, &mp_fops);

	return 0;
}

static void __exit mp_exit(void)
{
	mod_info("Unloading.");

	remove_proc_entry(MP_PROC_FILENAME, NULL);
}

module_init(mp_init);
module_exit(mp_exit);
