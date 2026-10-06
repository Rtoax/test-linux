#!/bin/bash
set -e

run() {
	echo -e "\033[1;32m${@}\033[m"
	eval "${@}"
}

cli() {
	run redis-cli "${@}"
}

key=user:1001

cli HSET ${key} name "Alice"
cli HSET ${key} age 25 city "Beijing"
cli HGET ${key} name
cli HMGET ${key} name age city
cli HGETALL ${key}

cli HKEYS ${key}
cli HVALS ${key}

cli HINCRBY ${key} age 5
cli HINCRBYFLOAT ${key} balance 10.5

cli HEXISTS ${key} name
cli HEXISTS ${key} email
cli HLEN ${key}
cli HDEL ${key} city
cli HGETALL ${key}

# NX: not-exist
cli HSETNX ${key} name "Bob"
