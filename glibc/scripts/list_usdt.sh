#!/bin/bash

if ! [[ -e /usr/bin/bpftrace ]]; then
	exit 0
fi

sudo bpftrace -l usdt:libc:*
