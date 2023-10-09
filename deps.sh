#!/bin/bash

pkgs=( make cmake gcc clang )
pkgs+=( systemtap-sdt-devel )

sudo dnf install -y ${pkgs[@]}
