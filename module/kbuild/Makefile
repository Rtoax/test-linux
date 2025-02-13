SHELL = bash
include ../../tlbuild.mk


KDIR = /lib/modules/`uname -r`/build

ccflags-y := -std=gnu99 -Wno-declaration-after-statement

kbuild:
		${Q}make -C $(KDIR) M=`pwd`

clean:
		${Q}make -C $(KDIR) M=`pwd` clean
