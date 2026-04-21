#!/bin/bash
set -e

. liblog.sh
. libfile.sh

ls="/usr/bin/ls"
qcow2=a.qcow2
GPT=a.img

qemu-img create -f qcow2 ${qcow2} 1G

cat>fdisk.out<<-EOF
g
w
EOF

dd if=/dev/zero of=${GPT} count=1 bs=1M
fdisk ${GPT} < fdisk.out

if [[ $(fexist /etc/os-release) != yes ]]; then
	error "fexist() test failed"
fi

if [[ $(ftype ${ls}) != elf ]] ||
   [[ $(ftype ${GPT}) != EFI-PART ]] ||
   [[ $(ftype ${qcow2}) != qcow2 ]]; then
	error "ftype() test failed"
fi
