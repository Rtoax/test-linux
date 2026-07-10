#!/bin/bash
# see ukify(1).
set -e

MACHINE_ID=$(cat /etc/machine-id)
[[ -z ${KVER} ]] && KVER=$(uname -r)

vmlinuz=/boot/vmlinuz-${KVER}
initrd=/boot/initramfs-${KVER}.img
test ! -f ${initrd} && initrd=/boot/initrd.img-${KVER}

# Example 1. Minimal invocation, see ukify(1)
# could use: --cmdline=@/etc/kernel/cmdline
sudo ukify build \
	--linux=${vmlinuz} \
	--initrd=${initrd} \
	--cmdline="rw quiet systemd.volatile=overlay" \
	--output=$PWD/Linux/${MACHINE_ID}-${KVER}.efi

# Then, generate addon images (.extra.d directory) with 'kernel-install'
# command.
#
# sudo kernel-install add ${KVER} /boot/vmlinuz-${KVER}
