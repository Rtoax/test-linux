#!/bin/bash
# see ukify(1).
set -e

build() {
	sudo ukify build "${@}"
}

vmlinuz=/boot/vmlinuz-$(uname -r)
initrd=/boot/initramfs-$(uname -r).img
test ! -f ${initrd} && initrd=/boot/initrd.img-$(uname -r)

# Example 1. Minimal invocation
build --linux=${vmlinuz} \
	--initrd=${initrd} \
	--cmdline="systemd.volatile=overlay"
