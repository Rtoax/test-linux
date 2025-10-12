#!/bin/bash
set -e

cat > multistrap.conf << EOF
[General]
arch=amd64
directory=$PWD/rootfs-ubuntu-amd64
cleanup=true
noauth=true
unpack=true
debootstrap=Ubuntu

[Ubuntu]
packages=apt coreutils sudo bash systemd network-manager vim
source=http://cn.archive.ubuntu.com/ubuntu/
suite=plucky
EOF

sudo multistrap -f multistrap.conf -d
