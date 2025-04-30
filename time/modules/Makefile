# SPDX-License-Identifier: GPL-3.0

obj-m += clock-accuracy.o
obj-m += mdelay.o msleep.o

CFLAGS_msleep.o := -DTEST_MSLEEP=1

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
