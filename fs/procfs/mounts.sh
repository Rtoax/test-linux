#!/bin/bash
set -e

dir=$(mktemp --directory proc-XXXXXX)

cleanup() {
	sudo umount ${dir} || true
	sudo rmdir ${dir}
}
trap cleanup EXIT

sudo mount -t proc proc ${dir}
ls ${dir}/
