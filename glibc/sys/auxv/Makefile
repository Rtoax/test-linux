SHELL = bash

TARGETS :=
TARGETS += getauxval

DEBUG = yes
CC = gcc

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

ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif


build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

getauxval: getauxval.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
