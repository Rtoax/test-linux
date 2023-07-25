#!/bin/bash

set -e

mkdir -p $PWD/tmpfs
sudo mount tmpfs -t tmpfs -o size=1G -o mode=0777 $PWD/tmpfs

rm -f testfile

make flock-3

# Holding the flock for seconds
./flock-3 $PWD/tmpfs/testfile &
# Make sure flock-3 above is running
sleep 0.5

# Resource temporarily unavailable until above flock-3 exit
while ! ./flock-3 $PWD/tmpfs/testfile; do :; done

while ! sudo umount $PWD/tmpfs; do :; done
rm -rf $PWD/tmpfs
