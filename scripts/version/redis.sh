#!/bin/bash
set -e
REDIS_CLI=$(which redis-cli 2>/dev/null || :)
REDIS_SERVER=$(which redis-server 2>/dev/null || :)
if [[ -z ${REDIS_CLI} ]]; then
	echo >&2 "ERROR: not found REDIS_CLI in your system"
	exit 0
fi

if [[ $1 == --name ]] || [[ $1 == --pretty-name ]]; then
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
