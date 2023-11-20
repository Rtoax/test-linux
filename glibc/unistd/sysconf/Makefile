
TARGETS := NPROCESSORS
TARGETS += sysconf

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | sed 's/"//g')

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif
ifdef STATIC
CFLAGS += -static
$(info Defined STATIC)
endif

.PHONY: build
build: confs_def.h ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

confs_def.h: sysconf.sh
	$(shell sh sysconf.sh)

# Add more object.o file
NPROCESSORS: NPROCESSORS.o
sysconf: sysconf.o

CFLAGS_NPROCESSORS := -D_NPROCESSORS=1
LDFLAGS_NPROCESSORS :=
CFLAGS_sysconf := -Wno-error

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o gen-sysconf-* confs_def.h
