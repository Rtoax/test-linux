#!/bin/bash
set -e

TARGET_ARCH="aarch64"
FEDORA_VERSION="41"
ROOTFS_DIR="/home/rongtao/fedora41-arm64-rootfs"
QEMU_BIN="/usr/bin/qemu-${TARGET_ARCH}-static"

sudo dnf install -y dnf-plugins-core qemu-user-static
sudo mkdir -p ${ROOTFS_DIR}

os_dnf() {
	sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${FEDORA_VERSION} \
		--forcearch=${TARGET_ARCH} \
		--use-host-config -y \
		"$@"
}

os_dnf group install development-tools
os_dnf install dnf make sudo rpm vim glibc-static

echo "Fedora ${FEDORA_VERSION} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
