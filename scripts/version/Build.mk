# SPDX-License-Identifier: GPL-3.0
target-prog-y += libbpf.sh libbpf.sh.1 libbpf.sh.2 libbpf.sh.3
target-prog-y += libxdp.sh libxdp.sh.1 libxdp.sh.2 libxdp.sh.3
target-prog-y += llvm.sh
target-prog-y += pciutils.sh
target-prog-y += procps-ng.sh
target-prog-y += gnome.sh
target-prog-y += make.sh make.sh.1 make.sh.2
target-prog-y += gdb.sh
target-prog-y += go.sh
target-prog-y += rocm.sh
target-prog-y += luca.sh
target-prog-y += hpcc.sh
target-prog-y += linux.sh
target-prog-y += linux.sh.1 linux.sh.2 linux.sh.3 linux.sh.4
target-prog-y += linux.sh.5 linux.sh.6 linux.sh.7 linux.sh.8
target-prog-y += systemd.sh
target-prog-y += uefi.sh uefi.sh.1 uefi.sh.2 uefi.sh.3
target-prog-y += java.sh java.sh.1 java.sh.2 java.sh.3
target-prog-y += numactl.sh
target-prog-y += pahole.sh pahole.sh.1 pahole.sh.2
target-prog-y += python.sh
target-prog-y += git.sh
target-prog-y += rust.sh
target-prog-y += shell.sh shell.sh.1 shell.sh.2
target-prog-y += openssl.sh
target-prog-y += strace.sh
target-prog-y += vim.sh vim.sh.1
target-prog-y += podman.sh
target-prog-y += ostree.sh
target-prog-y += psmisc.sh
target-prog-y += lsof.sh
target-prog-y += redis.sh redis.sh.1
target-prog-y += nasm.sh nasm.sh.1 nasm.sh.2 nasm.sh.3
target-prog-y += memcached.sh
target-prog-y += libvirt.sh libvirt.sh.1 libvirt.sh.2 libvirt.sh.3
target-prog-y += rpm.sh
target-prog-y += distro.sh distro.sh.1

# $1: script name without ext
define test_mmp
target-prog-y += ${1}.sh ${1}.sh.1 ${1}.sh.2 ${1}.sh.3
PROG_ARGS_${1}.sh.1 := --major
PROG_ARGS_${1}.sh.2 := --minor
PROG_ARGS_${1}.sh.3 := --patchlevel
endef

$(eval $(call test_mmp,bcc))
$(eval $(call test_mmp,binutils))
$(eval $(call test_mmp,bpftool))
$(eval $(call test_mmp,bpftrace))
$(eval $(call test_mmp,cmake))
$(eval $(call test_mmp,cuda))
$(eval $(call test_mmp,findutils))
$(eval $(call test_mmp,gcc))
$(eval $(call test_mmp,qemu))

PROG_ARGS_distro.sh.1 := short

PROG_ARGS_libvirt.sh.1 := --major
PROG_ARGS_libvirt.sh.2 := --minor
PROG_ARGS_libvirt.sh.3 := --patchlevel

PROG_ARGS_nasm.sh.1 := --major
PROG_ARGS_nasm.sh.2 := --minor
PROG_ARGS_nasm.sh.3 := --patchlevel

PROG_ARGS_redis.sh.1 := --name

PROG_ARGS_vim.sh.1 := sharepath

PROG_ARGS_shell.sh.1 := --name
PROG_ARGS_shell.sh.2 := --pretty-name

PROG_ARGS_pahole.sh.1 := --major
PROG_ARGS_pahole.sh.2 := --minor

PROG_ARGS_java.sh.1 := --major
PROG_ARGS_java.sh.2 := --minor
PROG_ARGS_java.sh.3 := --patchlevel

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

PROG_ARGS_make.sh.1 := --major
PROG_ARGS_make.sh.2 := --minor

PROG_ARGS_libxdp.sh.1 := --major
PROG_ARGS_libxdp.sh.2 := --minor
PROG_ARGS_libxdp.sh.3 := --patchlevel

PROG_ARGS_libbpf.sh.1 := --major
PROG_ARGS_libbpf.sh.2 := --minor
PROG_ARGS_libbpf.sh.3 := --patchlevel
