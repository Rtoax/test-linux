#!/bin/bash
set -e

pkgs=( make cmake gcc clang gdb )
pkgs+=( bpftrace bcc )         # eBPF
pkgs+=( criu )
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( gtk3-devel )           # GTK3
pkgs+=( kernel-devel )         # kernel
pkgs+=( libaio-devel )         # aio
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( libbpf-devel )         # libbpf
pkgs+=( libselinux-devel )     # SELinux
pkgs+=( liburing-devel )       # uring
pkgs+=( llvm )                 # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( ltrace )               # ltrace
pkgs+=( mmc )                  # mmc
pkgs+=( nasm )                 # nasm
pkgs+=( rust )                 # rustc
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( tree )

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf up -y
sudo dnf install ${args[@]} -y ${pkgs[@]}
