SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += list_static.o
obj-m += list_dynamic.o
obj-m += list_rcu.o
obj-m += list_rcu_example.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
