#!/bin/bash
set -ex

. /etc/os-release

TARGET_ARCH=$(uname -m)
ROOTFS_DIR="/home/rongtao/${ID}${VERSION_ID}-${TARGET_ARCH}-rootfs"

sudo dnf install -y dnf-plugins-core qemu-user-static
sudo mkdir -p ${ROOTFS_DIR}

os_dnf() {
	sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${VERSION_ID} \
		--forcearch=${TARGET_ARCH} \
		--use-host-config -y \
		"$@"
}

os_dnf group install development-tools
os_dnf install dnf make sudo rpm vim glibc-static

echo "${ID} ${VERSION_ID} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
