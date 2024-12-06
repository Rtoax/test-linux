SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


KDIR = /lib/modules/`uname -r`/build

ccflags-y := -std=gnu99 -Wno-declaration-after-statement

kbuild:
		${Q}make -C $(KDIR) M=`pwd`

clean:
		${Q}make -C $(KDIR) M=`pwd` clean
