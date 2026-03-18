# SPDX-License-Identifier: GPL-3.0
target-prog-y += llvm.sh
target-prog-y += pciutils.sh
target-prog-y += procps-ng.sh
target-prog-y += rocm.sh
target-prog-y += linux.sh
target-prog-y += linux.sh.1 linux.sh.2 linux.sh.3 linux.sh.4
target-prog-y += linux.sh.5 linux.sh.6 linux.sh.7 linux.sh.8
target-prog-y += systemd.sh
target-prog-y += uefi.sh uefi.sh.1 uefi.sh.2 uefi.sh.3
target-prog-y += pahole.sh pahole.sh.1 pahole.sh.2
target-prog-y += python.sh
target-prog-y += rust.sh
target-prog-y += shell.sh shell.sh.1 shell.sh.2
target-prog-y += strace.sh
target-prog-y += vim.sh vim.sh.1
target-prog-y += podman.sh
target-prog-y += ostree.sh
target-prog-y += psmisc.sh
target-prog-y += redis.sh redis.sh.1
target-prog-y += rpm.sh
target-prog-y += distro.sh distro.sh.1

# $1: script name without ext
define test_mmp
target-prog-y += ${1}.sh ${1}.sh.1 ${1}.sh.2 ${1}.sh.3
PROG_ARGS_${1}.sh.1 := --major
PROG_ARGS_${1}.sh.2 := --minor
PROG_ARGS_${1}.sh.3 := --patchlevel
endef

$(foreach software, bcc binutils bpftool bpftrace cmake cuda findutils gcc \
			gdb git gnome go hpcc java libbpf libvirt libxdp \
			llvm lsof luca make memcached nasm numactl openssl \
			qemu, \
  $(eval $(call test_mmp,${software})) \
)

PROG_ARGS_distro.sh.1 := short

PROG_ARGS_redis.sh.1 := --name

PROG_ARGS_vim.sh.1 := sharepath

PROG_ARGS_shell.sh.1 := --name
PROG_ARGS_shell.sh.2 := --pretty-name

PROG_ARGS_pahole.sh.1 := --major
PROG_ARGS_pahole.sh.2 := --minor

PROG_ARGS_uefi.sh.1 := --specmajor
PROG_ARGS_uefi.sh.2 := --specminor
PROG_ARGS_uefi.sh.3 := --vendor

PROG_ARGS_linux.sh.1 := --major
PROG_ARGS_linux.sh.2 := --patchlevel
PROG_ARGS_linux.sh.3 := --sublevel
PROG_ARGS_linux.sh.4 := --code
PROG_ARGS_linux.sh.5 := --uapimajor
PROG_ARGS_linux.sh.6 := --uapipatchlevel
PROG_ARGS_linux.sh.7 := --uapisublevel
PROG_ARGS_linux.sh.8 := --uapicode
