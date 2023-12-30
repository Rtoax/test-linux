#!/bin/bash
set -e

. /etc/os-release

OS=${ID}

echo "OS: ${OS}"

pkgs=( make cmake gcc clang gdb cgdb )
pkgs+=( gcc-aarch64-linux-gnu )
pkgs+=( bpftrace bpftool bcc ) # eBPF
pkgs+=( criu )
pkgs+=( dwarves )              # pahole
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( golang )               # go
pkgs+=( hwloc )                # lstopo
pkgs+=( inotify-tools )        # inotifywatch, ...
pkgs+=( llvm )                 # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( nasm )                 # nasm
pkgs+=( numactl )              # numastat
pkgs+=( python3-matplotlib )   # matplotlib
pkgs+=( python3-pyroute2 )     # pyroute2
pkgs+=( python3-scapy )
pkgs+=( qemu-kvm qemu-user )
pkgs+=( sparse )               # sparse
pkgs+=( strace )
pkgs+=( smartmontools )        # smartctl
pkgs+=( tree )

if [[ $(uname -m) == x86_64 ]]; then
	pkgs+=( glibc-devel.i686 )
fi

case ${OS} in
cclinux|fedora|centos|rhel)
	pkgs+=( bcc-devel )
	pkgs+=( binutils-devel )
	pkgs+=( capstone-devel )       # Capstone is a disassembly framework
	pkgs+=( cereal-devel )
	pkgs+=( clang-devel )
	pkgs+=( dtc )                  # device tree
	pkgs+=( elfutils-libelf-devel )
	pkgs+=( grub2-tools-minimal grub2-tools-extra )
	pkgs+=( gtest-devel gmock-devel )
	pkgs+=( gtk3-devel )           # GTK3
	pkgs+=( iproute-tc )           # tc
	pkgs+=( kernel-devel )         # kernel
	pkgs+=( libaio-devel )         # aio
	pkgs+=( libbpf-devel )         # libbpf
	pkgs+=( libpcap-devel )
	pkgs+=( libselinux-devel )     # SELinux
	pkgs+=( libunwind-devel )      # Unwind
	pkgs+=( liburing-devel )       # uring
	pkgs+=( libdwarf-tools )       # dwarfdump
	pkgs+=( llvm-devel )
	pkgs+=( ltrace )               # ltrace
	pkgs+=( mmc )                  # mmc
	pkgs+=( rust )                 # rustc
	pkgs+=( sg3_utils )            # sg_inq, etc.
	pkgs+=( systemtap-sdt-devel )  # sdt.h

	args=( --skip-broken )
	args+=( --nogpgcheck )

	sudo dnf up -y
	sudo dnf install ${args[@]} -y ${pkgs[@]}
	;;
debian|ubuntu)
	pkgs+=( libaio-dev )           # aio

	sudo apt install ${pkgs[@]}
	;;
*)
	echo "ERROR: Unknown OS ${OS}"
	;;
esac
