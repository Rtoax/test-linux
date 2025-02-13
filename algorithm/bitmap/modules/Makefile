include ../../../tlbuild.mk



obj-m += test_bitmap.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
