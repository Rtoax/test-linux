#!/bin/bash

QEMU=

make

if [[ $(readelf -h ./hello | grep X86-64 -o) ]]; then
	QEMU=qemu-x86_64
fi

${QEMU} -d in_asm,op,out_asm ./hello
