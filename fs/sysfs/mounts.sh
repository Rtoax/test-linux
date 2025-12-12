#!/bin/bash
set -e

dir=$(mktemp --directory sysfs-XXXXXX)

cleanup() {
	sudo umount ${dir} || true
	sudo rmdir ${dir}
}
trap cleanup EXIT

sudo mount -t sysfs sysfs ${dir}
ls ${dir}/
