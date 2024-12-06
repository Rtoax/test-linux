SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



obj-m += cn_test.o

TARGETS := ucon

all: ${TARGETS}
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@sudo insmod cn_test.ko
	@sudo ./ucon

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f ${TARGETS}
