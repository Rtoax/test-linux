#!/bin/bash

set -e

mkdir -p $PWD/tmpfs
sudo umount tmpfs || true

sudo mount tmpfs -t tmpfs -o size=1G -o mode=0777 $PWD/tmpfs

rm -f testfile

make flock

# Holding the flock for seconds
./flock $PWD/tmpfs/testfile &
# Make sure flock above is running
sleep 0.5

# Resource temporarily unavailable until above flock exit
while ! ./flock $PWD/tmpfs/testfile; do :; done

while ! sudo umount $PWD/tmpfs; do :; done
rm -rf $PWD/tmpfs
