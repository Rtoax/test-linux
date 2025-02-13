SHELL = bash
include ../../tlbuild.mk

include ../glibc.mk

SYMADDR___memcpy_ssse3 := $(call libc_sym_addr,__memcpy_ssse3)
SYMADDR___memcpy_generic := $(call libc_sym_addr,__memcpy_generic)
SYMADDR___memcpy_simd := $(call libc_sym_addr,__memcpy_simd)
SYMADDR___memcpy_a64fx := $(call libc_sym_addr,__memcpy_a64fx)

TARGETS :=
TARGETS += bcopy
TARGETS += index
TARGETS += memchr
TARGETS += memcpy memcpy-stress
ifneq ($(SYMADDR___memcpy_ssse3),)
  TARGETS += __memcpy_ssse3-stress
else
  $(warning Not found __memcpy_ssse3())
endif
ifneq ($(SYMADDR___memcpy_generic),)
  TARGETS += __memcpy_generic-stress
else
  $(warning Not found __memcpy_generic)
endif
ifneq ($(SYMADDR___memcpy_simd),)
  TARGETS += __memcpy_simd-stress
else
  $(warning Not found __memcpy_simd)
endif
ifneq ($(SYMADDR___memcpy_a64fx),)
  TARGETS += __memcpy_a64fx-stress
else
  $(warning Not found __memcpy_a64fx)
endif
TARGETS += memset memset-stress
TARGETS += memmove
TARGETS += stpcpy
TARGETS += strcmp
TARGETS += strcat
TARGETS += strchr
TARGETS += strcpy
TARGETS += strdupa
TARGETS += strdup
TARGETS += strlen
TARGETS += strncpy
TARGETS += strpbrk
TARGETS += strsep
TARGETS += strtok
TARGETS += strtol
TARGETS += strsignal
TARGETS += strerror strerror_r
TARGETS += strstr

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -O0 -g -ggdb
ifdef DEBUG
  CFLAGS += -DDEBUG
endif
ifdef RAND
  CFLAGS += -DRAND_MEM_POS=1
else
  $(warning WARNING: Enable random memory test with $$ make RAND=1)
endif
LDFLAGS :=

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
  TARGETS += __memcpy_aarch64-stress
  TARGETS += __memcpy_aarch64_sve-stress
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

.PHONY: build
build: sig.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

sig.h:
	$(shell bash signo.sh)

bcopy: bcopy.o
index: index.o
memchr: memchr.o
memcpy: memcpy.o
memcpy-stress: memcpy-stress.o proc.o
__memcpy_ssse3-stress: __memcpy_ssse3-stress.o proc.o
__memcpy_generic-stress: __memcpy_generic-stress.o proc.o
__memcpy_simd-stress: __memcpy_simd-stress.o proc.o
__memcpy_a64fx-stress: __memcpy_a64fx-stress.o proc.o
__memcpy_aarch64-stress: __memcpy_aarch64-stress.o proc.o
__memcpy_aarch64_sve-stress: __memcpy_aarch64_sve-stress.o proc.o
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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.log sig.h
