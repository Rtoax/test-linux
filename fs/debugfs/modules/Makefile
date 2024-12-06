SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += create-test1.o

KERNELROOT=/lib/modules/`uname -r`/build

all:
	${Q}make -C $(KERNELROOT) M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	${Q}make -C $(KERNELROOT) M=$(PWD) clean
