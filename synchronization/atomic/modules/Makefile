SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



obj-m += atomic-test0.o
obj-m += atomic64_test.o
obj-m += atomic_fetch_or_acquire.o
obj-m += atomic_try_cmpxchg_acquire.o
obj-m += xchg_relaxed.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
