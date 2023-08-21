#!/bin/bash

set -e

tmpfs=tmpfs.dir

clean() {
	sudo umount ${tmpfs} || true
	rm -rf ${tmpfs}
}

clean

mkdir ${tmpfs}
chmod 777 ${tmpfs}
sudo mount -t tmpfs -o size=50G none ${tmpfs}

pushd ${tmpfs}
# Trigger OOM
dd if=/dev/zero of=test.bin bs=512 count=1000000000
popd

clean
