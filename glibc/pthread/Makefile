include arch.mk

subdir-y := cache-misses
subdir-y += out-of-order
subdir-y += samples
subdir-y += scripts
subdir-${IS_X86_64} += pthread_self

target-libso-y := libpthread_helpers.so
target-liba-y := libpthread_helpers.a

libpthread_helpers.a-objs := pthread_helpers.a.o
libpthread_helpers.so-objs := pthread_helpers.so.o

include main.mk

pthread_helpers.so.o: pthread_helpers.h

pthread_helpers.a.o: pthread_helpers.h
