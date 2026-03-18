#!/bin/bash
# This script only display openssl version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
OPENSSL=$(which openssl 2>/dev/null || :)
if [[ -z ${OPENSSL} ]]; then
	echo >&2 "ERROR: not found OPENSSL in your system"
	exit 0
fi
${OPENSSL} --version 2>/dev/null | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | head -1 || {
	${OPENSSL} version 2>/dev/null | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | head -1
}
