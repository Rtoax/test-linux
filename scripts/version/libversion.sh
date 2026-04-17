#!/bin/bash

# $1: library name, like libbpf.so, libxdp.so
ldconfig_libver()
{
	# Opensuse has /sbin/ldconfig.
	LDCONFIG=$(which ldconfig 2>/dev/null || ls /sbin/ldconfig 2>/dev/null)
	realpath $(${LDCONFIG} -p | grep ${1} 2>/dev/null | \
			awk '{print $NF}' | \
			head -1 || :) 2>/dev/null || :
}
