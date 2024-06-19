#!/bin/bash

ld_so=$( which ld.so 2>/dev/null || true )
if [[ -z ${ld_so} ]]; then
	echo "WARNING: Not found ld.so"
	exit 0
fi
ld.so --list /bin/ls
