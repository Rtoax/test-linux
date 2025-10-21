# SPDX-License-Identifier: GPL-3.0
include ../glibc.mk

SYMADDR___memcpy_ssse3 := $(call libc_sym_addr,__memcpy_ssse3)
SYMADDR___memcpy_generic := $(call libc_sym_addr,__memcpy_generic)
SYMADDR___memcpy_simd := $(call libc_sym_addr,__memcpy_simd)
SYMADDR___memcpy_a64fx := $(call libc_sym_addr,__memcpy_a64fx)

target-y :=
target-y += bcopy
target-y += index
target-y += memchr
target-y += memcpy memcpy-stress
ifneq ($(SYMADDR___memcpy_ssse3),)
  target-y += __memcpy_ssse3-stress
else
  $(warning Not found __memcpy_ssse3())
endif
ifneq ($(SYMADDR___memcpy_generic),)
  target-y += __memcpy_generic-stress
else
  $(warning Not found __memcpy_generic)
endif
ifneq ($(SYMADDR___memcpy_simd),)
  target-y += __memcpy_simd-stress
else
  $(warning Not found __memcpy_simd)
endif
ifneq ($(SYMADDR___memcpy_a64fx),)
  target-y += __memcpy_a64fx-stress
else
  $(warning Not found __memcpy_a64fx)
endif
target-y += memset memset-stress
target-y += memmove
target-y += stpcpy
target-y += strcmp
target-y += strcat
target-y += strchr
target-y += strcpy
target-y += strdupa
target-y += strdup
target-y += strlen
target-y += strncpy
target-y += strpbrk
target-y += strsep
target-y += strtok
target-y += strtol
target-y += strsignal
target-y += strerror strerror_r
target-y += strstr
target-y += strspn

CFLAGS :=
CFLAGS += -I../../../
CFLAGS += -lm

ifdef RAND
  CFLAGS += -DRAND_MEM_POS=1
else
  $(warning WARNING: Enable random memory test with $$ make RAND=1)
endif
LDFLAGS :=

ifdef LD_BFD
  LDFLAGS += -fuse-ld=bfd
  $(info User linker bfd)
endif

include ../../compiler/cross-compile.mk

# https://github.com/ARM-software/optimized-routines
#
# libstringlib.a provides:
# memcpy()
#  __memcpy_aarch64()
#  __memcpy_aarch64_simd()
#  __memcpy_aarch64_mops()
#  __memcpy_aarch64_sve()
ARM_SOFTWARE_OPTIMIZED_ROUTINES_LIBSTRINGLIB_A ?= /usr/lib/libstringlib.a
ifneq ($(wildcard $(ARM_SOFTWARE_OPTIMIZED_ROUTINES_LIBSTRINGLIB_A)),)
  LDFLAGS += /usr/lib/libstringlib.a
  target-y += __memcpy_aarch64-stress
  target-y += __memcpy_aarch64_sve-stress
else
  $(warning "WARNING: Not found ARM-software/optimized-routines in your system")
  $(warning "         Need https://github.com/ARM-software/optimized-routines")
endif

ifdef SIMD
  CFLAGS += -mavx2
endif

CFLAGS_memcpy-stress := -DSTRESS=1
CFLAGS_memset-stress := -DSTRESS=1
CFLAGS___memcpy_ssse3-stress := -DSYMADDR___memcpy_ssse3=$(SYMADDR___memcpy_ssse3)
CFLAGS___memcpy_generic-stress := -DSYMADDR___memcpy_generic=$(SYMADDR___memcpy_generic)
CFLAGS___memcpy_simd-stress := -DSYMADDR___memcpy_simd=$(SYMADDR___memcpy_simd)
CFLAGS___memcpy_a64fx-stress := -DSYMADDR___memcpy_a64fx=$(SYMADDR___memcpy_a64fx)
CFLAGS___memcpy_aarch64-stress := -DARM_SOFTWARE___memcpy_aarch64=1
CFLAGS___memcpy_aarch64_sve-stress := -DARM_SOFTWARE___memcpy_aarch64_sve=1

target-prep-y := sig.h

include ../../template/main.mk

sig.h:
	$(shell bash signo.sh)

bcopy: bcopy.o
index: index.o
memchr: memchr.o
memcpy: memcpy.o
memcpy-stress: memcpy-stress.o proc_helpers.o
__memcpy_ssse3-stress: __memcpy_ssse3-stress.o proc_helpers.o
__memcpy_generic-stress: __memcpy_generic-stress.o proc_helpers.o
__memcpy_simd-stress: __memcpy_simd-stress.o proc_helpers.o
__memcpy_a64fx-stress: __memcpy_a64fx-stress.o proc_helpers.o
__memcpy_aarch64-stress: __memcpy_aarch64-stress.o proc_helpers.o
__memcpy_aarch64_sve-stress: __memcpy_aarch64_sve-stress.o proc_helpers.o
memset: memset.o
memset-stress: memset-stress.o
memmove: memmove.o
stpcpy: stpcpy.o
strcat: strcat.o
strchr: strchr.o
strcpy: strcpy.o
strcmp: strcmp.o
strdupa: strdupa.o
strdup: strdup.o
strlen: strlen.o
strncpy: strncpy.o
strpbrk: strpbrk.o
strsep: strsep.o
strtok: strtok.o
strtol: strtol.o
strsignal: strsignal.o
strerror: strerror.o
strerror_r: strerror_r.o
strstr: strstr.o
strspn: strspn.o
