#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

static int kernel_init(void)
{
	struct alt_instr *alt;
	struct alt_instr *begin = (struct alt_instr *)__alt_instructions;
	struct alt_instr *end = (struct alt_instr *)__alt_instructions_end;

	for (alt = begin; alt < end; alt++) {
		printk("instr_offset:%x, repl_offset:%x, cpuid:%x, instrlen:%x, replacementlen:%x\n",
			alt->instr_offset, alt->repl_offset, alt->cpuid,
			alt->instrlen, alt->replacementlen);
	}

	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
