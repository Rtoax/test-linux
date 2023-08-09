#!/bin/bash

set -e

tmpfs=tmpfs.dir

sudo umount ${tmpfs} || true
rm -rf ${tmpfs}

mkdir ${tmpfs}
chmod 777 ${tmpfs}
sudo mount -t tmpfs -o size=50G none ${tmpfs}

pushd ${tmpfs}
# Trigger OOM
dd if=/dev/zero of=test.bin bs=512 count=1000000000
popd
