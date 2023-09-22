TARGETS := currentel_user

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
obj-m += currentel.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all: ${TARGETS}
	make -C ${KERNELDIR} M=$(PWD) modules

currentel_user: currentel_user.o

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	make -C ${KERNELDIR} M=$(PWD) clean
	rm -f ${TARGETS} *.o *.d
