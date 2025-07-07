#!/bin/bash
set -e

QEMU=

make

if [[ $(readelf -h ./hello | grep X86-64 -o) ]]; then
	QEMU=qemu-x86_64
else
	echo "ERROR: Not support $(uname -m) or wrong hello format"
	echo "ERROR: $(file ./hello)"
	exit 1
fi

# out_asm show generated host assembly code for each compiled TB
# in_asm  show target assembly code for each compiled TB
# op      show micro ops for each compiled TB
${QEMU} -d in_asm,op,out_asm ./hello
