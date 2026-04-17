#!/bin/bash
set -e
REDIS_SERVER=$(which redis-server 2>/dev/null || :)
if [[ -z ${REDIS_SERVER} ]]; then
	echo >&2 "ERROR: not found redis-server in your system"
	exit 0
fi

if [[ $1 == --name ]] || [[ $1 == --pretty-name ]]; then
	if [[ "$(${REDIS_SERVER} --version | grep -wo Valkey)" ]]; then
		echo "Redis(Valkey)"
	else
		echo "Redis"
	fi
else
	$(dirname $(realpath $0))/version.sh -n redis -V -- ${@}
fi
