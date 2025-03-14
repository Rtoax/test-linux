include ../../../tlbuild.mk

TARGETS := hello
TARGETS += dbus_malloc

CC := gcc

CFLAGS := -Werror -Wall

LDFLAGS :=

CFLAGS += -DDEBUG -O0 -g
CFLAGS += $(shell pkg-config --cflags dbus-1)
LDFLAGS += $(shell pkg-config --libs dbus-1)

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o
dbus_malloc: dbus_malloc.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o
