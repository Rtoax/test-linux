include ../../../tlbuild.mk

TARGETS :=
TARGETS += getauxval
TARGETS += AT_ENTRY
TARGETS += AT_EXECFN
TARGETS += AT_HWCAP
TARGETS += AT_PAGESZ
TARGETS += AT_PHDR
TARGETS += AT_PLATFORM
TARGETS += AT_SYSINFO
TARGETS += AT_SYSINFO_EHDR

DEBUG := yes
CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -lm

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

include ../../../elf/pie.mk

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

getauxval: getauxval.o
AT_ENTRY: AT_ENTRY.o
AT_EXECFN: AT_EXECFN.o
AT_HWCAP: AT_HWCAP.o
AT_PAGESZ: AT_PAGESZ.o
AT_PHDR: AT_PHDR.o
AT_PLATFORM: AT_PLATFORM.o
AT_SYSINFO: AT_SYSINFO.o
AT_SYSINFO_EHDR: AT_SYSINFO_EHDR.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
