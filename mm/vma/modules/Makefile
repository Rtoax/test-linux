obj-m += init_mm.o
obj-m += listvma.o
obj-m += dump_mm.o
obj-m += dump_vma.o
obj-m += listvma-maps.o
obj-m += find_vma.o

PWD := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
