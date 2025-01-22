SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../glibc.mk

SYMADDR___memcpy_ssse3 := $(call libc_sym_addr,__memcpy_ssse3)
SYMADDR___memcpy_generic := $(call libc_sym_addr,__memcpy_generic)
SYMADDR___memcpy_simd := $(call libc_sym_addr,__memcpy_simd)

TARGETS :=
TARGETS += bcopy
TARGETS += index
TARGETS += memchr
TARGETS += memcpy memcpy-stress
ifneq ($(SYMADDR___memcpy_ssse3),)
  TARGETS += __memcpy_ssse3-stress
endif
ifneq ($(SYMADDR___memcpy_generic),)
  TARGETS += __memcpy_generic-stress
endif
ifneq ($(SYMADDR___memcpy_simd),)
  TARGETS += __memcpy_simd-stress
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

ifdef SIMD
  CFLAGS += -mavx2
endif

CFLAGS_memcpy-stress := -DSTRESS=1
CFLAGS_memset-stress := -DSTRESS=1
CFLAGS___memcpy_ssse3-stress := -DSYMADDR___memcpy_ssse3=$(SYMADDR___memcpy_ssse3)
CFLAGS___memcpy_generic-stress := -DSYMADDR___memcpy_generic=$(SYMADDR___memcpy_generic)
CFLAGS___memcpy_simd-stress := -DSYMADDR___memcpy_simd=$(SYMADDR___memcpy_simd)

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
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.log sig.h
