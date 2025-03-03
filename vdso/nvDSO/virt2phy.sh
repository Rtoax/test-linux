#!/bin/bash
set -ex

PROG_DIR=../../mm/

if [[ ! -e ${PROG_DIR} ]]; then
	echo "WARNING: sync git submodule first!!!"
	echo "syncing test-linux ..."
	timeout 10 git submodule update --init
	echo "syncing test-linux done"
fi

make -C ${PROG_DIR} clean
make -C ${PROG_DIR} virt2phy

rm -f virt2phy
cp ${PROG_DIR}/virt2phy .
#sudo LD_PRELOAD=./libnvdso.so ${PROG_DIR}/virt2phy
