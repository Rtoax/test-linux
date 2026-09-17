#!/bin/bash
set -e

key="zset2"

run() {
	echo -e "\033[1;32m${@}\033[m"
	eval "${@}"
}

zadd() {
	run redis-cli ZADD ${key} $@
}

trap "redis-cli ZRANGE ${key} 0 -1" EXIT

while true; do
	zadd 1 $(mktemp -u XXXXXXXXXXXXXXXXXXXX)
done
