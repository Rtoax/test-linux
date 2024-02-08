#!/bin/bash

run_dev() {
	LD_LIBRARY_PATH=$PWD ./dev
}

make clean
make

echo ==========================================================================
run_dev

rm libdev.so
ln -s libdev_hack.so libdev.so

echo ==========================================================================
run_dev

