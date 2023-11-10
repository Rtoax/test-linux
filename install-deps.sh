#!/bin/bash
set -e

pkgs=( make cmake gcc clang gdb )
pkgs+=( bpftrace bpftool bcc ) # eBPF
pkgs+=( binutils-devel )
pkgs+=( criu )
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( elfutils-libelf-devel )
pkgs+=( gtk3-devel )           # GTK3
pkgs+=( iproute-tc )           # tc
pkgs+=( kernel-devel )         # kernel
pkgs+=( libaio-devel )         # aio
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( libbpf-devel )         # libbpf
pkgs+=( libpcap-devel )
pkgs+=( libselinux-devel )     # SELinux
pkgs+=( liburing-devel )       # uring
pkgs+=( llvm )                 # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( ltrace )               # ltrace
pkgs+=( mmc )                  # mmc
pkgs+=( nasm )                 # nasm
pkgs+=( python3-pyroute2 )     # pyroute2
pkgs+=( rust )                 # rustc
pkgs+=( sg3_utils )            # sg_inq, etc.
pkgs+=( smartmontools )        # smartctl
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( tree )

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf up -y
sudo dnf install ${args[@]} -y ${pkgs[@]}
