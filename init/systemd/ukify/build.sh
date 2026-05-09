#!/bin/bash
# see ukify(1).
set -e

build() {
	sudo ukify build "${@}"
}

# Example 1. Minimal invocation
build --linux=/boot/vmlinuz-$(uname -r) \
	--initrd=/boot/initramfs-$(uname -r).img \
	--cmdline="systemd.volatile=overlay"
