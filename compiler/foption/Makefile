TARGETS :=
TARGETS += ffat-lto-objects
TARGETS += fpatchable-function-entry
TARGETS += flto
TARGETS += fwhole-program
TARGETS += fstack-protector fstack-protector-all fstack-protector-strong fstack-protector-explicit
TARGETS += fdump-ipa-all fdump-ipa-clones
TARGETS += fdump-tree-gimple
TARGETS += fdump-tree-all-raw fdump-tree-all
TARGETS += finput-charset

ifeq ($(shell uname -m),x86_64)
TARGETS += fcf-protection
endif

# command-line option ‘-fwpa’ is valid for LTO but not for C
# TARGETS += fwpa
# TARGETS += fltrans

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

# gcc: -fcf-protection=[full|branch|return|none|check]
CFLAGS_fcf-protection := -fcf-protection
CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
# N,M M=0 by default
CFLAGS_fpatchable-function-entry := -fpatchable-function-entry=5,2
CFLAGS_fwpa := -flto -fwpa
CFLAGS_flto := -flto=auto
CFLAGS_fwhole-program := -fwhole-program
CFLAGS_fltrans := -fltrans -fltrans-output-list=fltrans.txt
CFLAGS_fstack-protector := -fstack-protector
CFLAGS_fstack-protector-all := -fstack-protector-all
CFLAGS_fstack-protector-strong := -fstack-protector-strong
CFLAGS_fstack-protector-explicit := -fstack-protector-explicit
CFLAGS_fdump-ipa-all := -fdump-ipa-all
CFLAGS_fdump-ipa-clones := -fdump-ipa-clones
CFLAGS_fdump-tree-gimple := -fdump-tree-gimple
CFLAGS_fdump-tree-all-raw := -fdump-tree-all-raw
CFLAGS_fdump-tree-all := -fdump-tree-all
CFLAGS_finput-charset := -finput-charset=UTF-8

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

fcf-protection: fcf-protection.o
ffat-lto-objects: ffat-lto-objects.o
fpatchable-function-entry: fpatchable-function-entry.o
fwpa: fwpa.o
flto: flto.o
fwhole-program: fwhole-program.o
fltrans: fltrans.o
fstack-protector: fstack-protector.o
fstack-protector-all: fstack-protector-all.o
fstack-protector-explicit: fstack-protector-explicit.o
fstack-protector-strong: fstack-protector-strong.o
fdump-ipa-all: fdump-ipa-all.o
fdump-ipa-clones: fdump-ipa-clones.o
fdump-tree-gimple: fdump-tree-gimple.o
fdump-tree-all-raw: fdump-tree-all-raw.o
fdump-tree-all: fdump-tree-all.o
finput-charset: finput-charset.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	@$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s \
		fdump-ipa-all.c.* fdump-ipa-clones.c.* \
		fdump-tree-gimple.c.* \
		fdump-tree-all-raw.c.* fdump-tree-all.c.*
