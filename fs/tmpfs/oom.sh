#!/bin/bash
set -e

tmpfs=tmpfs.dir

clean() {
	sudo umount ${tmpfs} || true
	rm -rf ${tmpfs}
}
trap clean EXIT

clean

mkdir ${tmpfs}
chmod 777 ${tmpfs}
sudo mount -t tmpfs -o size=50G none ${tmpfs}

pushd ${tmpfs}
# Trigger OOM
dd if=/dev/zero of=test.bin bs=1M count=1000000000 status=progress
popd

