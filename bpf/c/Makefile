TARGETS := hello

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lbpf -lbcc

LDFLAGS :=
LDLIBS :=

CFLAGS += -DDEBUG -O0 -g

BPF_LOAD_PROGRAM = $(shell grep -row bpf_load_program /usr/include/bpf/bpf.h || true)
ifeq (${BPF_LOAD_PROGRAM}, bpf_load_program)
CFLAGS += -DHAVE_BPF_LOAD_PROGRAM=1
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
