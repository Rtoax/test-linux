
KDIR = /lib/modules/`uname -r`/build

ccflags-y := -std=gnu99 -Wno-declaration-after-statement
ccflags-y += -DCCFLAGS_Y=1

kbuild:
		${Q}make -C $(KDIR) M=`pwd`

clean:
		${Q}make -C $(KDIR) M=`pwd` clean
