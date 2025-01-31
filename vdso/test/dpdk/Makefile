# Rong Tao, 2022.05.09
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

ARCH := $(shell uname -m)

TARGETS :=

ifeq (${ARCH}, x86_64)
  TARGETS += tsc_freq_arch.o tsc_freq.o
endif

all: ${TARGETS}

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

#$(TARGETS): %:
#	@echo -e "  LD  \033[1;32m$(@)\033[m"
#	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test:
	gcc tsc_freq_arch.c -o tsc_freq_arch.out -DTEST
	gcc tsc_freq.c -o tsc_freq.out -DTEST

clean:
	${Q}rm -f *.o *.out
