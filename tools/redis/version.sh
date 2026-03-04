#!/bin/bash
# This script only display redis-cli version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
REDIS_CLI=$(which redis-cli 2>/dev/null || :)
if [[ -z ${REDIS_CLI} ]]; then
	echo >&2 "ERROR: not found REDIS_CLI in your system"
	exit 0
fi
${REDIS_CLI} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
