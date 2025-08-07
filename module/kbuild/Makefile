# NOTE: dnf install kernel-debug-devel kernel-debuginfo kernel-debug-modules
include ../kcompile.mk

build:
	${Q}make -C $(KDIR) M=`pwd`

clean:
	${Q}make -C $(KDIR) M=`pwd` clean
