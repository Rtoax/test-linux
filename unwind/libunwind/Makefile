
TARGETS :=
TARGETS += unw_regname
TARGETS += backtrace
TARGETS += do_backtrace

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS :=
CFLAGS += -lunwind
CFLAGS += -lunwind-x86_64

UNWIND_PTRACE=/lib64/libunwind-ptrace.a

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

unw_regname: unw_regname.o
backtrace: backtrace.o
do_backtrace: do_backtrace.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

${TARGETS}: %:
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<) ${UNWIND_PTRACE}

clean:
	rm -f ${TARGETS} *.o *.d
