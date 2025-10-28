#!/bin/bash
set -e

LINUX_ROOT=/home/rongtao/Git/linux/

linux_syscalls_name() {
	local tbl=$1
	cat ${1} | grep -E '^[0-9]' | awk '{print "  ["$1"] = \""$3"\","}'
}

ausyscall_name() {
	local arch=$1
	ausyscall --arch ${arch} --dump | grep -E '^[0-9]' | awk '{print "  ["$1"] = \""$2"\","}'
}

if [[ -e ${LINUX_ROOT} ]]; then
	linux_syscalls_name ${LINUX_ROOT}/arch/arm/tools/syscall.tbl | tee syscalls-arm.h
	ausyscall_name arm | tee syscalls-arm-au.h
	linux_syscalls_name ${LINUX_ROOT}/arch/arm64/tools/syscall_32.tbl | tee syscalls-arm32.h
	linux_syscalls_name ${LINUX_ROOT}/arch/arm64/tools/syscall_64.tbl | tee syscalls-arm64.h
	linux_syscalls_name ${LINUX_ROOT}/arch/mips/kernel/syscalls/syscall_n64.tbl | tee syscalls-mips64.h
	linux_syscalls_name ${LINUX_ROOT}/arch/x86/entry/syscalls/syscall_64.tbl | tee syscalls-x86_64.h
	linux_syscalls_name ${LINUX_ROOT}/arch/powerpc/kernel/syscalls/syscall.tbl | tee syscalls-ppc64.h
	linux_syscalls_name ${LINUX_ROOT}/arch/s390/kernel/syscalls/syscall.tbl | tee syscalls-s390.h
fi

