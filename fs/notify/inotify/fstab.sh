#!/bin/sh

while ! inotifywait -e modify /etc/fstab; do
	echo "Modify /etc/fstab"
	findmnt --verify --fstab --tab-file /etc/fstab
done
