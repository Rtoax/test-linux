# SPDX-License-Identifier: GPL-3.0
include json-c.mk
include helpers.mk

target-${HAVE_JSON_C} += config

target-prog-y += version.sh version.sh.1 version.sh.2 version.sh.3 version.sh.4
target-prog-y += version.sh.5 version.sh.6
target-prog-y += linux.sh
target-prog-y += linux.sh.1 linux.sh.2 linux.sh.3 linux.sh.4
target-prog-y += linux.sh.5 linux.sh.6 linux.sh.7 linux.sh.8
target-prog-y += linux-firmware.sh
target-prog-y += uefi.sh uefi.sh.1 uefi.sh.2 uefi.sh.3
target-prog-y += distro.sh distro.sh.1

# $1: script name without ext
define test_mmp
target-prog-y += ${1}.sh ${1}.sh.1 ${1}.sh.2 ${1}.sh.3 ${1}.sh.4 ${1}.sh.5
PROG_ARGS_${1}.sh.1 := --major
PROG_ARGS_${1}.sh.2 := --minor
PROG_ARGS_${1}.sh.3 := --patchlevel
PROG_ARGS_${1}.sh.4 := --name
PROG_ARGS_${1}.sh.5 := --pretty-name
endef

$(foreach software, bcc binutils bpftool bpftrace capstone cmake cuda dracut \
			ethtool findutils ffmpeg \
			gcc gdb git glibc gnome gnuplot go hpcc java kmod \
			latexmk libbpf libvirt libxdp \
			linux-firmware llvm lsof luca make memcached \
			nasm NetworkManager ndctl numactl openssl \
			ostree pahole pciutils podman procps-ng psmisc python \
			qemu redis rocm rpm rust shell sphinx strace systemd \
			util-linux vim, \
  $(eval $(call test_mmp,${software})) \
)

PROG_ARGS_version.sh := --name ALL
PROG_ARGS_version.sh.1 := --name ALL --check -E -K
PROG_ARGS_version.sh.2 := --name util-linux --check -L -K V
PROG_ARGS_version.sh.3 := --name bpftrace --check -L -K -E -V
PROG_ARGS_version.sh.4 := --name bpftrace
PROG_ARGS_version.sh.5 := --k2n sphinx --k2n bcc
PROG_ARGS_version.sh.6 := --e2n bt --e2n c

PROG_ARGS_distro.sh.1 := short

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

$(call target_link_helper,config,TLC_HELPERS)

LDFLAGS += -ljson-c
