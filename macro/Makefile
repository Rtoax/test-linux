# Contained in glibc-devel i686
GNU_STUBS_32_HDR = /usr/include/gnu/stubs-32.h

TARGETS :=
TARGETS += align
TARGETS += alias
TARGETS += arch
TARGETS += bit
TARGETS += likely
TARGETS += offsetof
TARGETS += __clang__
TARGETS += __nonnull
TARGETS += __restrict__
TARGETS += __func__
TARGETS += __linux__
TARGETS += __WORDSIZE __WORDSIZE-32
TARGETS += __TIME__
TARGETS += __VERSION__
TARGETS += __FILE__
TARGETS += machine
TARGETS += __ASSEMBLER__
TARGETS += ident
TARGETS += __GNUC__

TARGETS_CXX :=
TARGETS_CXX += __cplusplus

ifeq ($(shell uname -m),x86_64)
TARGETS += __i386__
TARGETS += __x86_64__
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += __aarch64__
# aarch64's gcc not support -m32
TARGETS := $(subst __WORDSIZE-32,,${TARGETS})
endif
ifeq ($(shell uname -m),sw_64)
# sw_64's gcc not support -m32
TARGETS := $(subst __WORDSIZE-32,,${TARGETS})
endif

# No m32 found
ifeq ($(wildcard $(GNU_STUBS_32_HDR)),)
$(warning "ERROR: Not found glibc-devel i686 headers")
TARGETS := $(subst __i386__,,${TARGETS})
TARGETS := $(subst __WORDSIZE-32,,${TARGETS})
endif

CC = gcc
CXX = c++

CFLAGS := -Werror -Wall
CFLAGS += -O0
CFLAGS += -DDEBUG -g

build: ${TARGETS} ${TARGETS_CXX}
	@echo
	@echo -e " \033[1;33m Done \033[m"

arch: arch.o
align: align.o
alias: alias.o
bit: bit.o
likely: likely.o
offsetof: offsetof.o
__clang__: __clang__.o
__i386__: __i386__.o
__x86_64__: __x86_64__.o
__aarch64__: __aarch64__.o
__nonnull: __nonnull.o
__cplusplus: __cplusplus.opp
__restrict__: __restrict__.o
__func__: __func__.o
__linux__: __linux__.o
__WORDSIZE: __WORDSIZE.o
__WORDSIZE-32: __WORDSIZE-32.o
__TIME__: __TIME__.o
__VERSION__: __VERSION__.o
__FILE__: __FILE__.o
machine: machine.o
__ASSEMBLER__: __ASSEMBLER__.o
ident: ident.o
__GNUC__: __GNUC__.o

CFLAGS___i386__ := -m32
CFLAGS___x86_64__ := -m64
CFLAGS___WORDSIZE-32 := -m32
CFLAGS_machine := -Wno-error=deprecated -Wno-deprecated

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.opp: %.cpp
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^)

$(TARGETS_CXX): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CXX) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^)

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_CXX} *.o *.opp
