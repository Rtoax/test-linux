#!/bin/bash
# debootstrap bootstraps a basic Debian system of suite into target from
# mirror by running script.
#
set -ex

# amd64, arm64, loong64, etc.
darch=
[[ ${DARCH} ]] && darch=${DARCH}
if [[ -z ${darch} ]]; then
	case $(uname -m) in
	x86_64) darch=amd64 ;;
	aarch64) darch=arm64 ;;
	esac
fi

mkdir rootfs-${darch}

debian12=( bookworm "http://deb.debian.org/debian/" )
ubuntu=( oracular "https://mirrors.tuna.tsinghua.edu.cn/ubuntu/" ./usr/share/debootstrap/scripts/bookworm )

os_ver=${ubuntu[0]}
os_repo=${ubuntu[1]}
os_script=${ubuntu[2]}

sudo debootstrap --arch=${darch} --foreign --no-check-gpg \
	${os_ver} \
	./rootfs-${darch} \
	${os_repo} ${os_script}
