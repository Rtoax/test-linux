#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <stdio.h>
#include <sys/sysinfo.h>


struct ram_occupy {
	unsigned long totalRamMemMb;
	unsigned long freeRamMemMb;
	unsigned long totalSwapMb;
	unsigned long freeSwapMb;
	/* like 80.23 % */
	struct {
		int integer;
		int decimal;
	} occupyRam, occupySwap;
};


void print_sysinfo(struct sysinfo *si)
{
	/* Conversion constants. */
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;

	printf("uptime      \t%ld days, %ld:%02ld:%02ld\n",
		si->uptime / day, (si->uptime % day) / hour,
		(si->uptime % hour) / minute, si->uptime % minute);
	printf("uptime      \t%ld.\n", si->uptime);
	printf("loads[0]    \t%ld.\n", si->loads[0]);
	printf("loads[1]    \t%ld.\n", si->loads[1]);
	printf("loads[2]    \t%ld.\n", si->loads[2]);
	printf("totalram    \t%ld.\n", si->totalram);
	printf("freeram     \t%ld.\n", si->freeram);
	printf("sharedram   \t%ld.\n", si->sharedram);
	printf("bufferram   \t%ld.\n", si->bufferram);
	printf("totalswap   \t%ld.\n", si->totalswap);
	printf("freeswap    \t%ld.\n", si->freeswap);
	printf("procs       \t%d.\n",  si->procs);
	printf("totalhigh   \t%ld.\n", si->totalhigh);
	printf("freehigh    \t%ld.\n", si->freehigh);
	printf("mem_unit    \t%d.\n", si->mem_unit);
}

void get_ram_usage(struct ram_occupy *info)
{
	const double megabyte = 1024 * 1024;
	struct sysinfo si;

	sysinfo(&si);
	print_sysinfo(&si);

	info->totalRamMemMb = (unsigned long)(si.totalram / megabyte);
	info->freeRamMemMb = (unsigned long)(si.freeram / megabyte);
	info->totalSwapMb = (unsigned long)(si.totalswap / megabyte);
	info->freeSwapMb = (unsigned long)(si.freeswap / megabyte);

	double occupyRam = (info->totalRamMemMb - info->freeRamMemMb) * 1.0 / info->totalRamMemMb;
	double occupySwap = (info->totalSwapMb - info->freeSwapMb) * 1.0 / info->totalSwapMb;

	info->occupyRam.integer = (int)(occupyRam * 100);
	info->occupyRam.decimal = (int)(occupyRam * 10000 / 100);
	info->occupySwap.integer = (int)(occupySwap * 100);
	info->occupySwap.decimal = (int)(occupySwap * 10000 / 100);
}

int main(void)
{
	struct ram_occupy info;

	get_ram_usage(&info);

	printf("RAM:  %d.%d%% \n", info.occupyRam.integer, info.occupyRam.decimal);
	printf("Swap: %d.%d%% \n", info.occupySwap.integer, info.occupySwap.decimal);

	return 0;
}
