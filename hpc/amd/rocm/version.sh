#!/bin/bash
# This script only display ROCm version, do not display other anything, because
# the git/hooks will use it.
set -e
HIPCC=$(which hipcc 2>/dev/null || :)
if [[ -z ${HIPCC} ]]; then
	echo >&2 "ERROR: not found hipcc in anywhere"
	return 0
fi
${HIPCC} --version | grep ^HIP | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
