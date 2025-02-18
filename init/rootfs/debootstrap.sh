#!/bin/bash
set -e

mkdir rootfs-arm64

sudo debootstrap \
	--arch=arm64 \
	--foreign \
	bookworm \
	./rootfs-arm64 \
	http://deb.debian.org/debian/
