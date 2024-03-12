
TARGETS := hello

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = clang

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LLVM_CFLAGS := $(shell llvm-config --cflags)

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

CFLAGS_hello +=

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S -emit-llvm $(<) -o $(<:.c=.ll)
	llvm-as $(<:.c=.ll) -o $(<:.c=.bc)
	llvm-dis $(<:.c=.bc) -o $(<:.c=.dis.ll)
	llc $(<:.c=.ll) -o $(<:.c=.s)
	# TODO: fatal error: 'stdio.h' file not found
	$(CC) -cc1 -ast-print $(<) || true

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.ll *.s *.bc
