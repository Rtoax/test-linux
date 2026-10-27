#!/bin/bash
set -e

. libos.sh
. liblog.sh

if [[ -z "$(is_os_any_of ${OS})" ]]; then
	error "is_os_any_of() failed"
fi
