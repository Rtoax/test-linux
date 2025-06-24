TARGETS := pthread_none
TARGETS += pthread_orig
TARGETS += pthread_pthread

CFLAGS :=
CFLAGS += -I$(shell realpath ../../../)

CFLAGS_pthread_none := -DSPIN_NONE
CFLAGS_pthread_orig := -DSPIN_ORIG
CFLAGS_pthread_pthread := -DSPIN_PTHREAD

include ../../../template/main.mk

pthread_none: pthread_none.o
pthread_orig: pthread_orig.o
pthread_pthread: pthread_pthread.o
