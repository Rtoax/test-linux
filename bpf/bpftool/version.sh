#!/bin/bash
# This script only display bpftool version, do not display other anything,
# because the git/hooks will use it.
set -e
BPFTOOL=$(which bpftool 2>/dev/null || :)
if [[ -z ${BPFTOOL} ]]; then
	echo >&2 "ERROR: not found BPFTOOL in your system"
	exit 0
fi
${BPFTOOL} --version | grep ^bpftool | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
