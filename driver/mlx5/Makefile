# SPDX-License-Identifier: GPL-3.0

obj-m += MLX5_GET.o

build:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
