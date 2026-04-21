#!/bin/bash
set -e

qemu() {
	./qemu-vm.sh "${@}"
}

dryrun() {
	qemu --dry-run "${@}"
}

qemu --help
qemu --cxl help
qemu --disk help
qemu --uefi help
