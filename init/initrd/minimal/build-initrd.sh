#!/bin/bash
set -ex

rm -rf rootfs
rm -f initrd.img

mkdir -p rootfs/bin
cp fakeinit rootfs/bin

pushd rootfs
mkdir -p sbin
ln -s bin/fakeinit init
pushd sbin
ln -s ../bin/fakeinit init
popd
popd

# Make initrd.img
pushd rootfs
find . | cpio -H newc -o | gzip -9 > ../initrd.img
popd
