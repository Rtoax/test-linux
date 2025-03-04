include ../../../tlbuild.mk


CC = gcc
LD = ld
NASM = $(shell which nasm 2>/dev/null)

TARGETS_C :=
TARGETS_AS :=
TARGETS_LDS :=

TARGETS_LDS += default.lds
TARGETS_C += main-c

ifeq ($(shell uname -m),x86_64)
  ifneq ($(NASM),)
    TARGETS_AS += hello-as
  endif
endif

# ld --verbose argument can print linker script
LDFLAGS_C := -Wl,-Tdefault.lds

all: ${TARGETS_LDS} ${TARGETS_AS} ${TARGETS_C}

main-c: main-c.o
hello-as: hello-as.o

default.lds:
	@echo -e "  LDS  generate \033[1;32m$(@)\033[m"
	${Q}./default.lds.sh

%.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(NASM) $(<) -felf64 -o $(@) $(CFLAGS) $(CFLAGS_$(*))

${TARGETS_AS}: %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(LD) -T $(@).ld -o $(@) $(LDFLAGS) $(LDFLAGS_$(*))

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_C): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_C) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_AS) $(TARGETS_C) $(TARGETS_LDS)\033[m"
	${Q}rm -f ${TARGETS_AS} ${TARGETS_C} ${TARGETS_LDS} *.o
