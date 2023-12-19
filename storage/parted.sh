#!/bin/bash

sudo parted -ls

mkgpt() {
	local disk=/dev/vdb

	sudo parted ${disk} mklabel gpt

	sudo parted ${disk} mkpart primary ext4 0 10M
	sudo parted ${disk} mkpart logical ext4 10M 20M
	sudo parted ${disk} mkpart extended ext4 20M 30M

	sudo mkfs.ext4 -T largefile ${disk}1
	sudo mkfs.ext4 -T largefile ${disk}2
	sudo mkfs.ext4 -T largefile ${disk}3

	sleep 1
	lsblk -o +fstype,uuid
}

mkgpt

