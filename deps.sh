#!/bin/bash

pkgs=( make cmake gcc clang )
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( libdwarf-tools )       # dwarfdump

sudo dnf install -y ${pkgs[@]}
