KDIR := /lib/modules/`uname -r`/build

build:
	${Q}make -C $(KDIR) M=`pwd`

clean:
	${Q}make -C $(KDIR) M=`pwd` clean
