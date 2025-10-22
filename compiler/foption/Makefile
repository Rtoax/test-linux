CC := gcc

include ../compiler.mk

subdir-y := bss
subdir-y += lto
subdir-y += ipa
subdir-y += sanitizer

target-y :=
target-y += fwhole-program
target-y += fstack-protector fstack-protector-all fstack-protector-strong fstack-protector-explicit
target-y += fdump-tree-gimple
target-y += fdump-tree-all-raw fdump-tree-all
target-y += finput-charset
target-y += fno-zero-initialized-in-bss fzero-initialized-in-bss
target-y += fplt fno-plt
target-y += fuse-ld
target-${CC_-fcf-protection} += fcf-protection
target-${CC_-fpatchable-function-entry} += fpatchable-function-entry

# command-line option ‘-fwpa’ is valid for LTO but not for C
# target-y += fwpa
# target-y += fltrans

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

target-clean-y := clean0

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

clean0:
	${Q}rm -rf fdump-tree-gimple.c.* \
		fdump-tree-all-raw.c.* fdump-tree-all.c.*
