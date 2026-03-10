target-y := hello
target-y += dbus_malloc

CFLAGS += $(shell pkg-config --cflags dbus-1)
LDFLAGS += $(shell pkg-config --libs dbus-1)

include main.mk
