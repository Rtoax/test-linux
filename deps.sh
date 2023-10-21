#!/bin/bash

pkgs=( make cmake gcc clang gdb )
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( bpftrace bcc )         # eBPF
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( mmc )                  # mmc
pkgs+=( lshw )                 # lshw
pkgs+=( nasm )                 # nasm

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf install ${args[@]} -y ${pkgs[@]}
