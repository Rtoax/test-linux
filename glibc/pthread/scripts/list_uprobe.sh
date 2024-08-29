#!/bin/bash

if ! [[ -e /usr/bin/bpftrace ]]; then
	exit 0
fi

. helpers.sh

lib=$(find_pthread_so)

sudo bpftrace -l uprobe:${lib}:*
