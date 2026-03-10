target-y := pthread_none
target-y += pthread_orig
target-y += pthread_pthread

CFLAGS += -I$(shell realpath ../../../)

CFLAGS_pthread_none := -DSPIN_NONE
CFLAGS_pthread_orig := -DSPIN_ORIG
CFLAGS_pthread_pthread := -DSPIN_PTHREAD

include main.mk
