#!/bin/bash
# This script only display redis version, do not display other anything, and
# don't execute failed, because the git/hooks will use it.
#
# Usage: redis.sh [--name]
#
set -e
REDIS_CLI=$(which redis-cli 2>/dev/null || :)
REDIS_SERVER=$(which redis-server 2>/dev/null || :)
if [[ -z ${REDIS_CLI} ]]; then
	echo >&2 "ERROR: not found REDIS_CLI in your system"
	exit 0
fi

if [[ $1 == --name ]]; then
	if [[ "$(${REDIS_SERVER} --version | grep -wo Valkey)" ]]; then
		echo "Redis(Valkey)"
	else
		echo "Redis"
	fi
else
	version=$(${REDIS_CLI} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

	source $(dirname $(realpath $0))/libversion.sh

	version_parser ${@} -- ${version}
fi
