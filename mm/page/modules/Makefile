
obj-m += alloc_page.o
obj-m += dump_page.o
obj-m += my_zero_pfn.o
obj-m += test_free_pages.o
#obj-m += walk_page_range.o
#obj-m += dump_pagetables.o # from arch/x86/mm/dump_pagetables.c
ifeq ($(shell uname -m),x86_64)
  obj-m += dumptab-x86.o
  obj-m += pagetable.o
endif
obj-m += PAGE_KERNEL.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
