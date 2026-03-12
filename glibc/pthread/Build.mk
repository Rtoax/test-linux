include arch.mk

subdir-y := cache-misses
subdir-y += out-of-order
subdir-y += samples
subdir-y += scripts
subdir-${IS_X86_64} += pthread_self

target-libso-y := libpthread_helpers.so
target-liba-y := libpthread_helpers.a

libpthread_helpers.a-objs := ${OUTPUT}pthread_helpers.a.o
libpthread_helpers.so-objs := ${OUTPUT}pthread_helpers.so.o
