#!/bin/bash
set -e

pkgs=( make cmake gcc clang gdb cgdb )
pkgs+=( gcc-aarch64-linux-gnu )
pkgs+=( bpftrace bpftool bcc ) # eBPF
pkgs+=( bcc-devel )
pkgs+=( binutils-devel )
pkgs+=( cereal-devel )
pkgs+=( clang-devel )
pkgs+=( criu )
pkgs+=( dtc )                  # device tree
pkgs+=( dwarves )              # pahole
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( elfutils-libelf-devel )
pkgs+=( grub2-tools-minimal grub2-tools-extra )
pkgs+=( gtest-devel gmock-devel )
pkgs+=( gtk3-devel )           # GTK3
pkgs+=( hwloc )                # lstopo
pkgs+=( inotify-tools )        # inotifywatch, ...
pkgs+=( iproute-tc )           # tc
pkgs+=( kernel-devel )         # kernel
pkgs+=( libaio-devel )         # aio
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( libbpf-devel )         # libbpf
pkgs+=( libpcap-devel )
pkgs+=( libselinux-devel )     # SELinux
pkgs+=( liburing-devel )       # uring
pkgs+=( llvm llvm-devel )      # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( ltrace )               # ltrace
pkgs+=( mmc )                  # mmc
pkgs+=( nasm )                 # nasm
pkgs+=( numactl )              # numastat
pkgs+=( python3-pyroute2 )     # pyroute2
pkgs+=( python3-matplotlib )   # matplotlib
pkgs+=( qemu-kvm qemu-user )
pkgs+=( rust )                 # rustc
pkgs+=( sg3_utils )            # sg_inq, etc.
pkgs+=( strace )
pkgs+=( smartmontools )        # smartctl
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( tree )

if [[ $(uname -m) == x86_64 ]]; then
	pkgs+=( glibc-devel.i686 )
fi

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf up -y
sudo dnf install ${args[@]} -y ${pkgs[@]}
