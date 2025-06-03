TARGETS := getspent
TARGETS += getspnam

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

include ../../template/main.mk

getspent: getspent.o shadow_helpers.o
getspnam: getspnam.o shadow_helpers.o
