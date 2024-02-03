#!/bin/bash
set -e

declare -a pkgs

. /etc/os-release

OS=${ID}

echo "OS: ${OS}"

# Install extra software package repo
case ${OS} in
centos|rhel|almalinux)
	sudo dnf install -y epel-release
	;;
fedora)
	;;
esac

pkgs+=( make cmake gcc clang gdb cgdb )
pkgs+=( gcc-aarch64-linux-gnu )
pkgs+=( bpftrace bcc )         # eBPF
pkgs+=( criu )
pkgs+=( dwarves )              # pahole
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( golang )               # go
pkgs+=( hwloc )                # lstopo
pkgs+=( inotify-tools )        # inotifywatch, ...
pkgs+=( llvm )                 # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( nasm )                 # nasm
pkgs+=( net-tools )            # netstat
pkgs+=( numactl )              # numastat
pkgs+=( opencl-headers )
pkgs+=( parallel )
pkgs+=( python3-matplotlib )   # matplotlib
pkgs+=( python3-pyroute2 )     # pyroute2
pkgs+=( python3-scapy )
pkgs+=( qemu-kvm qemu-user )
pkgs+=( sparse )               # sparse
pkgs+=( strace )
pkgs+=( smartmontools )        # smartctl
pkgs+=( tree )

# Desktop Packages
pkgs+=( terminator )

case ${OS} in
cclinux|fedora|centos|rhel|openEuler)
	if [[ $(uname -m) == x86_64 ]]; then
		pkgs+=( glibc-devel.i686 )
	fi
	pkgs+=( bcc-devel )
	pkgs+=( binutils-devel )
	pkgs+=( bpftool )
	pkgs+=( capstone-devel )       # Capstone is a disassembly framework
	pkgs+=( cereal-devel )
	pkgs+=( clang-devel )
	pkgs+=( dtc )                  # device tree
	pkgs+=( elfutils-libelf-devel )
	pkgs+=( git-clang-format )
	pkgs+=( grub2-tools-minimal grub2-tools-extra )
	pkgs+=( gtest-devel gmock-devel )
	pkgs+=( gtk3-devel )           # GTK3
	pkgs+=( iproute-tc )           # tc
	pkgs+=( jemalloc-devel )
	pkgs+=( kernel-devel )         # kernel
	pkgs+=( libaio-devel )         # aio
	pkgs+=( libbpf-devel )         # libbpf
	pkgs+=( libpcap-devel )
	pkgs+=( libselinux-devel )     # SELinux
	pkgs+=( libunwind-devel )      # Unwind
	pkgs+=( liburing-devel )       # uring
	pkgs+=( libdwarf-tools )       # dwarfdump
	pkgs+=( llvm-devel )
	pkgs+=( lsb_release )
	pkgs+=( ltrace )               # ltrace
	pkgs+=( mmc )                  # mmc
	pkgs+=( mpich mpich-devel )    # mpi
	pkgs+=( rust )                 # rustc
	pkgs+=( scl-utils )
	pkgs+=( sg3_utils )            # sg_inq, etc.
	pkgs+=( systemtap-sdt-devel )  # sdt.h

	args=( --skip-broken )
	args+=( --nogpgcheck )

	sudo dnf up -y
	sudo dnf install ${args[@]} -y ${pkgs[@]}
	;;
debian|ubuntu)
	pkgs+=( clang-format )
	pkgs+=( libaio-dev )           # aio
	pkgs+=( libmpich-dev )         # MPI
	pkgs+=( linux-tools-common )
	pkgs+=( lsb-release )

	args=( --fix-missing )

	sudo apt update -y
	sudo apt list --upgradable
	sudo apt upgrade -y
	sudo apt install ${args[@]} ${pkgs[@]}
	;;
*)
	echo "ERROR: Unknown OS ${OS}"
	;;
esac
