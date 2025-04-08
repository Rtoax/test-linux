# SPDX-License-Identifier: GPL-3.0

obj-m += relocation.o
ifeq ($(shell uname -m),aarch64)
  obj-m += big-module.o
  obj-m += big-module-data.o
  obj-m += big-module-text.o
endif

CFLAGS_big-module-data.o := -DBIG_DATA=1
CFLAGS_big-module-text.o := -DBIG_TEXT=1

# If KBUILD_CFLAGS is empty, insmod error happen:
#  [ 1108.381641] module: overflow in relocation type 10 val ffffffffc0860068
#  [ 1108.381645] module: `relocation' likely not compiled with -mcmodel=kernel
ifdef OVERFLOW
KBUILD_CFLAGS :=
endif

KBUILD_CFLAGS += -Wno-unused-function
KBUILD_CFLAGS += -Wno-unused-variable
KBUILD_CFLAGS += -Wno-missing-prototypes

all: big-text.h generated_functions.h
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	${Q}du -sh *.ko

generated_functions.h: generate_code.py
	${Q}./generate_code.py

big-text.h: big-text.sh
	${Q}bash big-text.sh

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	${Q}rm -f big-text.h generated_functions.h
