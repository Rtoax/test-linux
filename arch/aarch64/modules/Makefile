

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += currentel_user
obj-m += currentel.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all: ${TARGETS}
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

currentel_user: currentel_user.o

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
	rm -f ${TARGETS} *.o *.d
