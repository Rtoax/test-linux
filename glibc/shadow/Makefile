target-y := getspent
target-y += getspnam

CFLAGS :=
CFLAGS += -I../../
CFLAGS += -pthread

include main.mk

getspent: getspent.o shadow_helpers.o
getspnam: getspnam.o shadow_helpers.o
