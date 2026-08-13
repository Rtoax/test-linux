#!/bin/bash
set -e

. libcpu.sh

if [[ -z "$(is_arch $(uname -m))" ]]; then
	error "is_arch() failed"
fi
