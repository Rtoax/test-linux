CC := gcc

include ../compiler.mk

sub-dir := bss
sub-dir += lto
sub-dir += ipa

TARGETS :=
TARGETS += fwhole-program
TARGETS += fstack-protector fstack-protector-all fstack-protector-strong fstack-protector-explicit
TARGETS += fdump-tree-gimple
TARGETS += fdump-tree-all-raw fdump-tree-all
TARGETS += finput-charset
TARGETS += fno-zero-initialized-in-bss fzero-initialized-in-bss
TARGETS += fplt fno-plt
TARGETS += fuse-ld
TARGETS += fsanitize
TARGETS_CPP += fsanitize_cpp

ifeq ($(CC_-fcf-protection),1)
  TARGETS += fcf-protection
endif

# command-line option ‘-fwpa’ is valid for LTO but not for C
# TARGETS += fwpa
# TARGETS += fltrans

ifeq ($(CC_-fpatchable-function-entry),1)
  TARGETS += fpatchable-function-entry
endif

CFLAGS :=

# gcc: -fcf-protection=[full|branch|return|none|check]
CFLAGS_fcf-protection := -fcf-protection
# N,M M=0 by default
CFLAGS_fpatchable-function-entry := -fpatchable-function-entry=5,2
CFLAGS_fwpa := -flto -fwpa
LDFLAGS_fwhole-program := -fwhole-program
ifneq ($(CC),clang)
  CFLAGS_fstack-protector-explicit := -fstack-protector-explicit
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
# Depends on libasan
CFLAGS_fsanitize := -fsanitize=address
ifneq ($(CC),clang)
  CFLAGS_fsanitize += -Wno-error=stringop-overflow
endif
LDFLAGS_fsanitize := ${CFLAGS_fsanitize}

CXXFLAGS_fsanitize_cpp := ${CFLAGS_fsanitize}
CXXFLAGS_fsanitize_cpp += -Wno-error=stringop-overflow
LDXXFLAGS_fsanitize_cpp := ${LDFLAGS_fsanitize}

TARGETS_CLEAN := clean0

include ../../template/main.mk

fcf-protection: fcf-protection.o
fpatchable-function-entry: fpatchable-function-entry.o
fwpa: fwpa.o
fwhole-program: fwhole-program.o
fltrans: fltrans.o
fstack-protector: fstack-protector.o
fstack-protector-all: fstack-protector-all.o
fstack-protector-explicit: fstack-protector-explicit.o
fstack-protector-strong: fstack-protector-strong.o
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
fsanitize_cpp: fsanitize_cpp.opp

clean0:
	${Q}rm -rf fdump-tree-gimple.c.* \
		fdump-tree-all-raw.c.* fdump-tree-all.c.*
