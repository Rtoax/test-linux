#!/bin/bash
# spdk: https://github.com/spdk/spdk.git

SPDK_PREFIX=/usr/local/

# GCC FDO
export CFLAGS="-fprofile-generate=$PWD -lgcov"
export LDFLAGS="-lgcov -fprofile-arcs"

./configure \
	--prefix=$SPDK_PREFIX \
	--disable-tests \
	--disable-unit-tests \
	--disable-apps \
	--without-vhost \
	--without-crypto \
	--without-rbd \
	--with-rdma \
	--without-iscsi-initiator \
	--without-vtune \
	--with-shared

make -j4
