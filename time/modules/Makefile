# SPDX-License-Identifier: GPL-3.0

obj-m += clock-accuracy.o
obj-m += mdelay.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
