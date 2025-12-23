# SPDX-License-Identifier: GPL-3.0
__USE_PROC_HELPERS__ = y

include glibc.mk

SYMADDR___memcpy_ssse3 := $(call libc_sym_addr,__memcpy_ssse3)
SYMADDR___memcpy_erms := $(call libc_sym_addr,__memcpy_erms)
SYMADDR___memcpy_generic := $(call libc_sym_addr,__memcpy_generic)
SYMADDR___memcpy_simd := $(call libc_sym_addr,__memcpy_simd)
SYMADDR___memcpy_a64fx := $(call libc_sym_addr,__memcpy_a64fx)

# $1: memcpy name, like __memcpy_ssse3
define add_glibc_obj
  SYMADDR_${1} := $(call libc_sym_addr,${1})
  ifneq ($(SYMADDR_${1}),)
    target-y += ${1}-stress
    CFLAGS_${1}-stress += -DSYMADDR_${1}=$(SYMADDR_${1})
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

target-prep-y := sig.h

include main.mk

sig.h:
	$(shell bash signo.sh)

bcopy: bcopy.o
index: index.o
memchr: memchr.o
memcpy: memcpy.o
memcpy-stress: memcpy-stress.o ${PROC_HELPERS}
__memcpy_ssse3-stress: __memcpy_ssse3-stress.o ${PROC_HELPERS}
__memcpy_erms-stress: __memcpy_erms-stress.o ${PROC_HELPERS}
__memcpy_generic-stress: __memcpy_generic-stress.o ${PROC_HELPERS}
__memcpy_simd-stress: __memcpy_simd-stress.o ${PROC_HELPERS}
__memcpy_a64fx-stress: __memcpy_a64fx-stress.o ${PROC_HELPERS}
__memcpy_aarch64-stress: __memcpy_aarch64-stress.o ${PROC_HELPERS}
__memcpy_aarch64_simd-stress: __memcpy_aarch64_simd-stress.o ${PROC_HELPERS}
__memcpy_aarch64_sve-stress: __memcpy_aarch64_sve-stress.o ${PROC_HELPERS}
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
strstr-cpp: strstr.cpp.o
