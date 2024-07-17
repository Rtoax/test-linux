SHELL = bash

TARGETS :=
TARGETS += mbranch-protection

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

include ../../scripts/check_compiler_option.mk

pac-ret := $(findstring 1,$(call check_compiler_option,$(CC),-mbranch-protection=pac-ret))

ifeq (${pac-ret},1)
  CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
else
  $(warning "$(CC) not support -mbranch-protection=pac-ret")
endif
ifeq ($(shell uname -m),aarch64)
CFLAGS_mbranch-protection += -march=armv8.3-a
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

mbranch-protection: mbranch-protection.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	@$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
