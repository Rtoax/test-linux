# Reference: https://lwn.net/Articles/383962/
#

INCLUDES = -I. -I$(KDIR)/include
KBUILD_CFLAGS += -g

obj-m	+= sillymod.o
obj-m	+= sillymod-event.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

CFLAGS_sillymod-event.o = -I$(src)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
