SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += _Complex_I _Complex __complex__
TARGETS += creal cimag
TARGETS += int
TARGETS += math

CC = gcc

CFLAGS ?=
CFLAGS += -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wno-error=unused-variable
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
# FIXME
CFLAGS += -Wno-unused-variable

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

LDFLAGS := -lm

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

_Complex_I: _Complex_I.o
_Complex: _Complex.o
__complex__: __complex__.o
creal: creal.o
cimag: cimag.o
int: int.o
math: math.o

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
