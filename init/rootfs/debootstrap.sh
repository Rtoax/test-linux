#!/bin/bash
# debootstrap bootstraps a basic Debian system of suite into target from
# mirror by running script.
set -e

# amd64, arm64, loong64, etc.
darch=
[[ ${DARCH} ]] && darch=${DARCH}
[[ -z ${darch} ]] && darch=arm64

mkdir rootfs-${darch}

sudo debootstrap \
	--arch=${darch} \
	--foreign \
	bookworm \
	./rootfs-${darch} \
	http://deb.debian.org/debian/
