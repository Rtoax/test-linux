#!/bin/bash
set -e

libdir=$PWD
run_dev() {
	LD_LIBRARY_PATH=$libdir ./dev
}

make

echo ==========================================================================
run_dev

rm libdev.so
ln -s libdev_hack.so libdev.so

echo ==========================================================================
run_dev

echo ==========================================================================

rm -rf rootfs.out
mkdir rootfs.out
cp libdev.so.1 rootfs.out
pushd rootfs.out
ln -s libdev.so.1 libdev.so
popd

libdir=$PWD/rootfs.out
run_dev
