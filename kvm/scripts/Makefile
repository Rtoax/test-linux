SHELL = bash
include ../../tlbuild.mk


# Just support x86_64 right now
ifeq ($(shell uname -m),x86_64)
TARGETS := ioctl_values
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = clang

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

ioctl_values: ioctl_values.o

build: ${TARGETS}
	@echo -e "\033[1;32mExamples: \033[m"
	@echo -e "\033[1;33m./ioctl_values 2>/dev/null | awk '{print \"@ioctls[\"\$$3\"] = \"\$$1\";\"}'\033[m"

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

