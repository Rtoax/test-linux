#!/bin/bash
set -e

. liblog.sh
. libfile.sh

ls="/usr/bin/ls"

if [[ $(fexist /etc/os-release) != yes ]]; then
	error "fexist() test failed"
fi

if [[ $(ftype ${ls}) != elf ]]; then
	error "ftype() test failed"
fi
