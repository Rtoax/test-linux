#!/bin/bash
set -e

. libos.sh
. liblog.sh

if [[ -z "$(is_os ${OS})" ]]; then
	error "is_os() failed"
fi
