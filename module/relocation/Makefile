SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



obj-m += relocation.o

# If KBUILD_CFLAGS is empty, insmod error happen:
#  [ 1108.381641] module: overflow in relocation type 10 val ffffffffc0860068
#  [ 1108.381645] module: `relocation' likely not compiled with -mcmodel=kernel
ifdef OVERFLOW
KBUILD_CFLAGS :=
endif

KBUILD_CFLAGS += -Wno-unused-function
KBUILD_CFLAGS += -Wno-unused-variable

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
