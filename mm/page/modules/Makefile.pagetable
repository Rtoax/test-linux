obj-m += pagetable.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f mmap hugepage

load:
	sudo rmmod pagetable.ko
	sudo insmod pagetable.ko

huge_prep:
	mount -t hugetlbfs nodev /huge
	echo 1024 | sudo tee /proc/sys/vm/nr_hugepages
	cat /proc/meminfo | grep Huge
		
huge:
	cc hugepage.c -o hugepage

mmap:
	cc mmap.c -o mmap
