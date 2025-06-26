# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

TARGETS := hello
TARGETS_LLVM_LL := hello_ll

obj-ast := $(addsuffix .ast, $(TARGETS))
obj-ll := $(addsuffix .ll, $(TARGETS))
obj-ll.s := $(addsuffix .ll.s, $(TARGETS))
obj-bc := $(addsuffix .bc, $(TARGETS))
obj-dis.ll := $(addsuffix .dis.ll, $(TARGETS))

TARGETS_POST := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-dis.ll}

include ../../../template/main.mk

hello: hello.o
hello_ll: hello.ll

#%.o: %.c
#	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
#	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
#	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S -emit-llvm $(<) -o $(<:.c=.ll)
#	${Q}$(LLVM_AS) $(<:.c=.ll) -o $(<:.c=.bc)
#	${Q}$(LLVM_DIS) $(<:.c=.bc) -o $(<:.c=.dis.ll)
#	${Q}$(LLC) $(<:.c=.ll) -o $(<:.c=.s)
#	# TODO: fatal error: 'stdio.h' file not found
#	${Q}$(CC) -cc1 -ast-print $(<) || true
