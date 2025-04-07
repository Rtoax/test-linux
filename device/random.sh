#!/bin/bash
set -ex

DEV=/dev/random

[[ $(basename $0) == urandom.sh ]] && DEV=/dev/urandom

rand_0xffff_1() {
	echo 0x$(od -An -N2 -t x2 ${DEV} | awk '{print $1}')
}

rand_0xffffffff_1() {
	echo 0x$(od -An -N4 -t x4 ${DEV} | awk '{print $1}')
}

rand_0xffff_2() {
	echo $RANDOM
}

rand_0xffff_3() {
	echo 0x$(openssl rand -hex 2)
}

od -N 32 -t x1 ${DEV}
od -N 32 -t x2 ${DEV}
od -An -N 32 -t x2 ${DEV}
