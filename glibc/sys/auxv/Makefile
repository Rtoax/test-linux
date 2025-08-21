targets := getauxval
targets += AT_ENTRY
targets += AT_EXECFN
targets += AT_HWCAP
targets += AT_PAGESZ
targets += AT_PHDR
targets += AT_PLATFORM
targets += AT_SYSINFO
targets += AT_SYSINFO_EHDR

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
