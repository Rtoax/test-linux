#!/bin/bash
set -e

. liblog.sh
. libfile.sh

ls="/usr/bin/ls"
qcow2=a.qcow2

qemu-img create -f qcow2 ${qcow2} 1G

if [[ $(fexist /etc/os-release) != yes ]]; then
	error "fexist() test failed"
fi

if [[ $(ftype ${ls}) != elf ]] ||
   [[ $(ftype ${qcow2}) != qcow2 ]]; then
	error "ftype() test failed"
fi
