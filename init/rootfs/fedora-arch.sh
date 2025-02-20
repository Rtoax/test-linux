#!/bin/bash
set -e

TARGET_ARCH="aarch64"
FEDORA_VERSION="41"
ROOTFS_DIR="/home/rongtao/fedora41-arm64-rootfs"
QEMU_BIN="/usr/bin/qemu-${TARGET_ARCH}-static"

sudo dnf install -y dnf-plugins-core qemu-user-static
sudo mkdir -p ${ROOTFS_DIR}

sudo dnf --installroot=${ROOTFS_DIR} \
	--releasever=${FEDORA_VERSION} \
	--forcearch=${TARGET_ARCH} \
	--use-host-config \
	group install development-tools

echo "Fedora ${FEDORA_VERSION} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
