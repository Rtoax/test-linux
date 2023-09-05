#!/bin/bash

set -ex

create_disk() {
	sudo modprobe nbd max_part=16
	lsmod | grep nbd
	sudo rm -f test.qcow2
	sudo qemu-img create -f qcow2 test.qcow2 128G
	sudo qemu-nbd --connect /dev/nbd0 test.qcow2 -f qcow2
	sudo chown rongtao:rongtao test.qcow2
}

partition() {
	sudo fdisk -l /dev/nbd0
	cat >tmp.txt<<-EOF
	n
	p
	1
	2048
	100M
	w
	EOF
	sudo fdisk /dev/nbd0 < tmp.txt
	rm tmp.txt
}

makefs() {
	sudo mkfs.fat /dev/nbd0p1
	mkdir fat.out
	sudo mount /dev/nbd0p1 fat.out
	pushd fat.out
	# FIXME: Add more file
	sudo sh -c 'echo "RT" > README'
	popd
	sudo umount fat.out
	rmdir fat.out
}

destroy() {
	sudo umount fat.out || true
	sudo rm -rf fat.out || true
	sudo qemu-nbd --disconnect /dev/nbd0 || true
	sudo rmmod nbd || true
}
trap destroy EXIT

create_disk
partition
makefs
