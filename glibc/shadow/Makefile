targets := getspent
targets += getspnam

CFLAGS :=
CFLAGS += -I../../
CFLAGS += -pthread

include ../../template/main.mk

getspent: getspent.o shadow_helpers.o
getspnam: getspnam.o shadow_helpers.o
