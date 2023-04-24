ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
obj-m += invalid_opcode_kern.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C ${KERNELDIR} M=$(PWD) modules
	gcc invalid_opcode_user.c -o invalid_opcode_user
	gcc cpuid_user.c -o cpuid_user

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	make -C ${KERNELDIR} M=$(PWD) clean
	rm -f invalid_opcode_user cpuid_user
