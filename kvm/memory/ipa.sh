#!/bin/bash
# GPA (IPA in arm)
#
if [[ $(uname -m) != aarch64 ]]; then
	echo "ERROR: Only aarch64 has IPA"
	exit 1
fi
dmesg | grep 'IPA Size Limit'
