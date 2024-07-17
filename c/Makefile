SHELL = bash

TARGETS :=
TARGETS += auto
TARGETS += array
TARGETS += ascii
TARGETS += arch-unsigned-signed
TARGETS += alignas
TARGETS += case
TARGETS += const
TARGETS += dummy
TARGETS += param-pass
TARGETS += compat
TARGETS += compare
TARGETS += _Generic
TARGETS += goto
TARGETS += ptr-dim
TARGETS += struct
TARGETS += xor
TARGETS += __alignof__
TARGETS += __has_include
TARGETS += __label__
TARGETS += __typeof__
TARGETS += NULL
TARGETS += _Nullable
TARGETS += _Nonnull
TARGETS += BUILD_BUG_ON_ZERO
TARGETS += macro
TARGETS += while
TARGETS += stub
TARGETS += if
TARGETS += enum
TARGETS += __STDC__
TARGETS += include_next
TARGETS += unsigned

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

ifeq ("", "$(CROSS_COMPILE)")
  MK_ARCH="${shell uname -m}"
else
  MK_ARCH="${shell echo $(CROSS_COMPILE) | sed -n 's/^[[:space:]]*\([^\/]*\/\)*\([^-]*\)-[^[:space:]]*/\2/p'}"
endif

AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
ifneq ($(shell $(CROSS_COMPILE)ld.bfd -v 2> /dev/null),)
  LD = $(CROSS_COMPILE)ld.bfd
else
  LD = $(CROSS_COMPILE)ld
endif

LDFLAGS :=
LDLIBS :=

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/

ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    CFLAGS += -mcpu=sw8a
  endif
  ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    CFLAGS += -mcpu=sw6b
  endif
endif

ifdef STATIC
  CFLAGS += -static
  $(info Defined STATIC)
endif

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif

# For CROSS_COMPILE
ifdef SYSROOT
  CFLAGS += --sysroot=$(SYSROOT)
endif

CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
CFLAGS_alignas := -std=gnu17
CFLAGS_if := -Wno-error=unused-value -Wno-unused-value
CFLAGS__Generic := -Wno-all
CFLAGS_case := -Wno-error=unused-label -Wno-unused-label
CFLAGS_include_next := -Dinclude/ -Wno-error

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
auto: auto.o
ascii: ascii.o
alignas: alignas.o
arch-unsigned-signed: arch-unsigned-signed.o
case: case.o
const: const.o
param-pass: param-pass.o
array: array.o
compat: compat.o
compare: compare.o
dummy: dummy.o
_Generic: _Generic.o
goto: goto.o
ptr-dim: ptr-dim.o helpers.o
struct: struct.o
xor: xor.o
__alignof__: __alignof__.o
__has_include: __has_include.o
__label__: __label__.o
__typeof__: __typeof__.o
NULL: NULL.o
_Nullable: _Nullable.o
_Nonnull: _Nonnull.o
BUILD_BUG_ON_ZERO: BUILD_BUG_ON_ZERO.o
macro: macro.o
while: while.o
stub: stub.o
if: if.o
enum: enum.o
__STDC__: __STDC__.o
include_next: include_next.o
unsigned: unsigned.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@:.o=.pic.o) -c $(<) -fpic
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.pic.s) -fpic
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -E $(<) -o $(<:.c=.E.c)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s *.E.c
