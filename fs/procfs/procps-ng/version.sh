#!/bin/bash
# This script only display ps version, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
set -e
PS=$(which ps 2>/dev/null || :)
if [[ -z ${PS} ]]; then
	echo >&2 "ERROR: not found PS in your system"
	exit 0
fi
${PS} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
