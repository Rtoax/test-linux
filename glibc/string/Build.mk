# SPDX-License-Identifier: GPL-3.0
include glibc.mk
include helpers.mk

# $1: memcpy name, like __memcpy_ssse3
define add_glibc_obj
  SYMADDR_${1} := $(call glibc_sym_addr,${1})
  ifneq ($$(SYMADDR_${1}),)
    target-y += ${1}-stress
    ${1}-stress-objs := ${PROC_HELPERS}
    CFLAGS_${1}-stress += -DSYMADDR_${1}=$${SYMADDR_${1}}
  else
    $$(warning Not found ${1}())
  endif
endef

target-y += bcopy
target-y += index
target-y += memchr
target-y += memcpy memcpy-stress
$(eval $(call add_glibc_obj,__memcpy_ssse3))
$(eval $(call add_glibc_obj,__memcpy_erms))
$(eval $(call add_glibc_obj,__memcpy_generic))
$(eval $(call add_glibc_obj,__memcpy_simd))
$(eval $(call add_glibc_obj,__memcpy_a64fx))
$(eval $(call add_glibc_obj,__memcpy_avx512_unaligned))
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

target-cpp-y := strstr-cpp

prep-y := sig.h

memcpy-stress-objs := ${PROC_HELPERS}
strstr-cpp-objs := strstr.cpp.o

CFLAGS_strcat := -Wno-error=stringop-overflow
CFLAGS_strcpy := -Wno-error=stringop-overflow

CFLAGS += -I../../../
LDFLAGS += -lm

ifdef RAND
  CFLAGS += -DRAND_MEM_POS=1
else
  $(warning WARNING: Enable random memory test with $$ make RAND=1)
endif

ifdef LD_BFD
  LDFLAGS += -fuse-ld=bfd
  $(info User linker bfd)
endif

include cross-compile.mk

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
  target-y += __memcpy_aarch64-stress
  target-y += __memcpy_aarch64_simd-stress
  target-y += __memcpy_aarch64_sve-stress

  __memcpy_aarch64-stress-objs := ${PROC_HELPERS}
  __memcpy_aarch64_simd-stress-objs := ${PROC_HELPERS}
  __memcpy_aarch64_sve-stress-objs := ${PROC_HELPERS}

  LDFLAGS += /usr/lib/libstringlib.a
else
  $(warning "WARNING: Not found ARM-software/optimized-routines in your system")
  $(warning "         Need https://github.com/ARM-software/optimized-routines")
endif

ifdef SIMD
  CFLAGS += -mavx2
endif

CFLAGS_memcpy-stress := -DSTRESS=1
CFLAGS_memset-stress := -DSTRESS=1
CFLAGS___memcpy_aarch64-stress := -DARM_SOFTWARE___memcpy_aarch64=1
CFLAGS___memcpy_aarch64_simd-stress := -DARM_SOFTWARE___memcpy_aarch64_simd=1
CFLAGS___memcpy_aarch64_sve-stress := -DARM_SOFTWARE___memcpy_aarch64_sve=1
