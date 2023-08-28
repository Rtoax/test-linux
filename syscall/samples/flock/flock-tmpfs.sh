#!/bin/bash

set -e

release() {
	sudo umount $PWD/tmpfs || true
	rm -rf $PWD/tmpfs
}
trap release EXIT

mkdir -p $PWD/tmpfs

sudo mount tmpfs -t tmpfs -o size=1G -o mode=0777 $PWD/tmpfs


make flock

# Holding the flock for seconds
./flock $PWD/tmpfs/testfile 3 &

# Make sure flock above startup already
sleep 0.5

# Resource temporarily unavailable until above flock exit
while ! ./flock $PWD/tmpfs/testfile; do :; done

