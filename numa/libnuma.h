#pragma once

/* If not found any node mem info in dmesg, some APIs return this. */
#define DMESG_NUMA_MEM_INVALID	0xDEAD0000

int print_numa_mem(void);
int phy_addr_numa(unsigned long paddr);
int virt_addr_numa(unsigned long vaddr);
