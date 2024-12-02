SHELL = bash

KDIR = /lib/modules/`uname -r`/build

ccflags-y := -std=gnu99 -Wno-declaration-after-statement

kbuild:
		make -C $(KDIR) M=`pwd`

clean:
		make -C $(KDIR) M=`pwd` clean
