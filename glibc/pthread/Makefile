include ../../template/arch.mk

subdir-y := cache-misses
subdir-y += out-of-order
subdir-y += samples
subdir-y += scripts
subdir-${IS_X86_64} += pthread_self

target-libso-y := libpthread_helpers.so

include ../../template/main.mk

pthread_helpers.so.o: pthread_helpers.h
libpthread_helpers.so: pthread_helpers.so.o
