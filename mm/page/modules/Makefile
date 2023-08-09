obj-m += alloc_page.o
obj-m += dump_page.o
obj-m += my_zero_pfn.o
obj-m += test_free_pages.o
#obj-m += walk_page_range.o
obj-m += walk_page_table.o
obj-m += dumptab-x86.o
obj-m += pagetable.o
#obj-m += dump_pagetables.o # from arch/x86/mm/dump_pagetables.c

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
