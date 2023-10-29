#!/bin/bash
set -e

pkgs=( make cmake gcc clang gdb )
pkgs+=( bpftrace bcc )         # eBPF
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( gtk3-devel )           # GTK3
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( lshw )                 # lshw
pkgs+=( ltrace )               # ltrace
pkgs+=( mmc )                  # mmc
pkgs+=( nasm )                 # nasm
pkgs+=( rust )                 # rustc
pkgs+=( systemtap-sdt-devel )  # sdt.h

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf up -y
sudo dnf install ${args[@]} -y ${pkgs[@]}
