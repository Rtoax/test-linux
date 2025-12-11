// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022-2025 Rong Tao <rtoax@foxmail.com>

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>
#include <linux/entry-common.h>
#include <linux/perf_event.h>
#include <linux/kernel_stat.h>
#include <linux/mc146818rtc.h>
#include <linux/acpi_pmtmr.h>
#include <linux/clockchips.h>
#include <linux/interrupt.h>
#include <linux/memblock.h>
#include <linux/ftrace.h>
#include <linux/ioport.h>
#include <linux/export.h>
#include <linux/syscore_ops.h>
#include <linux/delay.h>
#include <linux/timex.h>
#include <linux/i8253.h>
#include <linux/dmar.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/dmi.h>
#include <linux/smp.h>
#include <linux/mm.h>

#include <asm/trace/irq_vectors.h>
#include <asm/irq_remapping.h>
#include <asm/perf_event.h>
#include <asm/x86_init.h>
#include <linux/atomic.h>
#include <asm/mpspec.h>
#include <asm/i8259.h>
#include <asm/proto.h>
#include <asm/traps.h>
#include <asm/apic.h>
#include <asm/acpi.h>
#include <asm/io_apic.h>
#include <asm/desc.h>
#include <asm/hpet.h>
#include <asm/mtrr.h>
#include <asm/time.h>
#include <asm/smp.h>
#include <asm/mce.h>
#include <asm/tsc.h>
#include <asm/hypervisor.h>
#include <asm/cpu_device_id.h>
#include <asm/intel-family.h>
#include <asm/irq_regs.h>

/**
 *	Failed, 这些变量在源码中已经有了，并且该文件编译不通过
 */
#define LAPIC_CAL_LOOPS		(HZ/10)

static __initdata int lapic_cal_loops = -1;
static __initdata long lapic_cal_t1, lapic_cal_t2;
static __initdata unsigned long long lapic_cal_tsc1, lapic_cal_tsc2;
static __initdata unsigned long lapic_cal_pm1, lapic_cal_pm2;
static __initdata unsigned long lapic_cal_j1, lapic_cal_j2;

static void __init livepatch_lapic_cal_handler(struct clock_event_device *dev)
{
	unsigned long long tsc = 0;
	long tapic = apic_read(APIC_TMCCT);
	unsigned long pm = acpi_pm_read_early();

	if (boot_cpu_has(X86_FEATURE_TSC))
		tsc = rdtsc();

	switch (lapic_cal_loops++) {
	case 0:
		lapic_cal_t1 = tapic;
		lapic_cal_tsc1 = tsc;
		lapic_cal_pm1 = pm;
		lapic_cal_j1 = jiffies;
		break;

	case LAPIC_CAL_LOOPS:
		lapic_cal_t2 = tapic;
		lapic_cal_tsc2 = tsc;
		if (pm < lapic_cal_pm1)
			pm += ACPI_PM_OVRRUN;
		lapic_cal_pm2 = pm;
		lapic_cal_j2 = jiffies;
		break;
	}
}

static struct klp_func funcs[] = {
	{
		.old_name = "lapic_cal_handler",
		.new_func = livepatch_lapic_cal_handler
	}, { }
};

static struct klp_object objs[] = {
	{
		/* name being NULL means vmlinux */
		.funcs = funcs,
	}, { }
};

static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};

static int test_klp_livepatch_init(void)
{
	return klp_enable_patch(&patch);
}

static void test_klp_livepatch_exit(void)
{
}

module_init(test_klp_livepatch_init);
module_exit(test_klp_livepatch_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
MODULE_AUTHOR("Rong Tao <rtoax@foxmail.com>");
MODULE_DESCRIPTION("Livepatch test: livepatch module");
