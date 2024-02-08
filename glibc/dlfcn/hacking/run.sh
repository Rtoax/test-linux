#!/bin/bash

run_dev() {
	LD_LIBRARY_PATH=$PWD ldd ./dev
	LD_LIBRARY_PATH=$PWD ./dev
}

run_dev

rm libdev.so
ln -s libdev_hack.so libdev.so

run_dev

