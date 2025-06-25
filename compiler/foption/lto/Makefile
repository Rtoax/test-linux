include ../../compiler.mk

TARGETS :=
TARGETS += ffat-lto-objects
TARGETS += flto

CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
CFLAGS_flto := -flto=auto
LDFLAGS_flto := -flto=auto

include ../../../template/main.mk

ffat-lto-objects: ffat-lto-objects.o
flto: flto.o
