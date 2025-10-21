include ../../compiler.mk

target-y :=
target-y += ffat-lto-objects
target-y += flto

CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
CFLAGS_flto := -flto=auto
LDFLAGS_flto := -flto=auto

include ../../../template/main.mk

ffat-lto-objects: ffat-lto-objects.o
flto: flto.o
