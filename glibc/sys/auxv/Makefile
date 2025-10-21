target-y := getauxval
target-y += AT_ENTRY
target-y += AT_EXECFN
target-y += AT_HWCAP
target-y += AT_PAGESZ
target-y += AT_PHDR
target-y += AT_PLATFORM
target-y += AT_SYSINFO
target-y += AT_SYSINFO_EHDR

CFLAGS := -lm

include ../../../template/main.mk

getauxval: getauxval.o
AT_ENTRY: AT_ENTRY.o
AT_EXECFN: AT_EXECFN.o
AT_HWCAP: AT_HWCAP.o
AT_PAGESZ: AT_PAGESZ.o
AT_PHDR: AT_PHDR.o
AT_PLATFORM: AT_PLATFORM.o
AT_SYSINFO: AT_SYSINFO.o
AT_SYSINFO_EHDR: AT_SYSINFO_EHDR.o
