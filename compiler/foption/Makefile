include ../../tlbuild.mk

CC := gcc

include ../compiler.mk

sub-dir := bss
sub-dir += lto

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

TARGETS :=
TARGETS += fwhole-program
TARGETS += fstack-protector fstack-protector-all fstack-protector-strong fstack-protector-explicit
TARGETS += fdump-ipa-all fdump-ipa-clones
TARGETS += fdump-tree-gimple
TARGETS += fdump-tree-all-raw fdump-tree-all
TARGETS += finput-charset
TARGETS += fno-zero-initialized-in-bss fzero-initialized-in-bss
TARGETS += fplt fno-plt
TARGETS += fuse-ld
TARGETS += fsanitize

ifeq ($(CC_-fcf-protection),1)
  TARGETS += fcf-protection
endif

# command-line option ‘-fwpa’ is valid for LTO but not for C
# TARGETS += fwpa
# TARGETS += fltrans

ifeq ($(CC_-fpatchable-function-entry),1)
  TARGETS += fpatchable-function-entry
endif

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

# gcc: -fcf-protection=[full|branch|return|none|check]
CFLAGS_fcf-protection := -fcf-protection
# N,M M=0 by default
CFLAGS_fpatchable-function-entry := -fpatchable-function-entry=5,2
CFLAGS_fwpa := -flto -fwpa
LDFLAGS_fwhole-program := -fwhole-program
ifneq ($(CC),clang)
  CFLAGS_fstack-protector-explicit := -fstack-protector-explicit
  CFLAGS_fdump-ipa-all := -fdump-ipa-all
  CFLAGS_fdump-ipa-clones := -fdump-ipa-clones
  CFLAGS_fdump-tree-gimple := -fdump-tree-gimple
  CFLAGS_fdump-tree-all-raw := -fdump-tree-all-raw
  CFLAGS_fdump-tree-all := -fdump-tree-all
endif
CFLAGS_fltrans := -fltrans -fltrans-output-list=fltrans.txt
CFLAGS_fstack-protector := -fstack-protector
CFLAGS_fstack-protector-all := -fstack-protector-all
CFLAGS_fstack-protector-strong := -fstack-protector-strong
CFLAGS_finput-charset := -finput-charset=UTF-8
CFLAGS_fno-zero-initialized-in-bss := -fno-zero-initialized-in-bss -DUNINITIALIZED_VALUES=1
CFLAGS_fzero-initialized-in-bss := -fzero-initialized-in-bss -DUNINITIALIZED_VALUES=1
CFLAGS_fplt := -fplt
CFLAGS_fno-plt := -fno-plt
# Use the bfd linker instead of the default linker. There are bfd, gold, lld,
# mold, etc. optional linkers.
LDFLAGS_fuse-ld := -fuse-ld=bfd
CFLAGS_fsanitize := -fsanitize=address
ifneq ($(CC),clang)
  CFLAGS_fsanitize += -Wno-error=stringop-overflow
endif
LDFLAGS_fsanitize := ${CFLAGS_fsanitize}

.PHONY: build
build: ${TARGETS} ${sub-dir-build}
	@echo -e "  CC = ${CC}"
	@echo -e "  CFLAGS = ${CFLAGS}"
	@echo -e " \033[1;33m Done \033[m"

fcf-protection: fcf-protection.o
fpatchable-function-entry: fpatchable-function-entry.o
fwpa: fwpa.o
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
fno-zero-initialized-in-bss: fno-zero-initialized-in-bss.o
fzero-initialized-in-bss: fzero-initialized-in-bss.o
fplt: fplt.o
fno-plt: fno-plt.o
fuse-ld: fuse-ld.o
fsanitize: fsanitize.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=-nof.s) $(CFLAGS) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s \
		fdump-ipa-all.c.* fdump-ipa-clones.c.* \
		fdump-tree-gimple.c.* \
		fdump-tree-all-raw.c.* fdump-tree-all.c.*

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
