#!/bin/bash

set -e

pre_clean() {
	sudo rm -f test.qcow2
}
create_disk() {
	pre_clean
	sudo modprobe nbd max_part=16
	lsmod | grep nbd
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
	n
	p
	2


	w
	EOF
	sudo fdisk /dev/nbd0 < tmp.txt
	sudo fdisk -l /dev/nbd0
}

makefs() {
	sudo mkfs.fat /dev/nbd0p1
	mkdir fat.out
	sudo mount /dev/nbd0p1 fat.out
	pushd fat.out
	# FIXME: Add more file
	sudo sh -c 'echo "RT is fat" > README'
	popd
	sudo mkfs.ext4 /dev/nbd0p2
	mkdir ext4.out
	sudo mount /dev/nbd0p2 ext4.out
	pushd ext4.out
	# FIXME: Add more file
	sudo sh -c 'echo "RT is ext4" > README'
	popd
}

destroy() {
	sudo umount fat.out || true
	sudo rm -rf fat.out || true
	sudo umount ext4.out || true
	sudo rm -rf ext4.out || true
	sudo qemu-nbd --disconnect /dev/nbd0 || true
	sudo rmmod nbd || true
	sudo rm tmp.txt || true
}

usage()
{
	cat <<-EOF

	--nofs
	--nodestroy
	-v, --verbose
	-h, --help

	EOF
}

fs_flag=YES
destroy_flag=YES

while true
do
case $1 in
-v | --verbose)
	shift
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
	;;
-h | --help)
	shift
	usage
	exit 0
	;;
--nofs)
	shift
	fs_flag=
	;;
--nodestroy)
	shift
	destroy_flag=
	;;
*)
	break
	;;
esac
done

[[ ! -z ${destroy_flag} ]] && trap destroy EXIT

create_disk

if [[ ! -z ${fs_flag} ]]; then
	partition
	makefs
fi
