targets := hello
targets += dbus_malloc

CFLAGS += $(shell pkg-config --cflags dbus-1)
LDFLAGS += $(shell pkg-config --libs dbus-1)

include ../../../template/main.mk

hello: hello.o
dbus_malloc: dbus_malloc.o
