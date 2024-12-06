# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


###############################################################################
# Kernel
obj-m += invalid_opcode_kern.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

###############################################################################
# User
sub-dir :=

TARGETS :=
CFLAGS :=
ARCH_LIB_CPUID :=

# User
ifeq ($(shell uname -m),x86_64)
  sub-dir += avx
  sub-dir += tsc
  sub-dir += pku
  sub-dir += sse

  ifneq ($(shell lscpu | grep -w avx2),)
    CFLAGS += -mavx2 -mfma
    CFLAGS += -DCPU_HAVE_AVX2=1
  endif
  ifneq ($(shell lscpu | grep -w avx512f),)
    CFLAGS += -mavx512f -mfma
    CFLAGS += -DCPU_HAVE_AVX512F=1
  endif
  TARGETS += add-x86
  TARGETS += bts
  TARGETS += invalid_opcode_user
  TARGETS += fsin
  TARGETS += bswapl
  TARGETS += _mm_clflush
  TARGETS += prefetch
  TARGETS += rte_memcpy
  TARGETS += vgetbv
  TARGETS += stosb memset
  TARGETS += nop
  TARGETS += rdmsr
  ifneq ($(shell lscpu | grep -w rdrand),)
    TARGETS += rdrand
  endif
  ifneq ($(shell lscpu | grep -w rdseed),)
  TARGETS += rdseed
  endif

  ARCH_LIB_CPUID += cpuid-x86.o
endif

ifeq ($(shell uname -m),aarch64)
  sub-dir += neon
  sub-dir += sve

  # Check cpu flags
  ifneq ($(shell lscpu | grep -w sve),)
    CFLAGS += -DCPU_HAVE_SVE=1
    CFLAGS += -march=armv8-a+sve
  endif
  ifneq ($(shell lscpu | grep -w sve2),)
    CFLAGS += -DCPU_HAVE_SVE2=1
    CFLAGS += -march=armv8-a+sve2
  endif

  CFLAGS += -DCPU_HAVE_NEON=1
  TARGETS += mrs

  ARCH_LIB_CPUID += cpuid-arm64.o
endif

TARGETS += udiv div
TARGETS += simd
TARGETS += cpuid_user

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: user
user: $(TARGETS) $(sub-dir-build)

kernel:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules


add-x86: add-x86.o
bts: bts.o
bswapl: bswapl.o
invalid_opcode_user: invalid_opcode_user.o
cpuid_user: cpuid_user.o ${ARCH_LIB_CPUID}
_mm_clflush: _mm_clflush.o
prefetch: prefetch.o
rte_memcpy: rte_memcpy.o
fsin: fsin.o
udiv: udiv.o
div: div.o
vgetbv: vgetbv.o
stosb: stosb.o
memset: memset.o
nop: nop.o
rdmsr: rdmsr.o
mrs: mrs.o
simd: simd.o
rdrand: rdrand.o
rdseed: rdseed.o

#CFLAGS += -Werror -Wall
CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread

CFLAGS += -no-pie

ifdef STATIC
  CFLAGS += -static
  $(info Defined STATIC)
endif
ifdef DEBUG
  CFLAGS += -DDEBUG=1
  $(info Defined DEBUG)
endif

CFLAGS_rdrand := -mrdrnd
CFLAGS_rdseed := -mrdseed
CFLAGS_udiv := -O0
CFLAGS_div := -O0

ifdef IGNORE_RETURN_VALUE
  CFLAGS_udiv += -DIGNORE_RETURN_VALUE=1
  CFLAGS_div += -DIGNORE_RETURN_VALUE=1
endif

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

help:
	@echo "make [kernel|user|help]"
	@echo " default: user"

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@echo "empty, [cd $(PWD)] to insmod"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o
	${Q}make -C ${KERNELDIR} M=$(PWD) clean

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
