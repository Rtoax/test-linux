#!/bin/bash
set -e

run() {
	echo -e "\033[1;32m${@}\033[m"
	eval "${@}"
}

cli() {
	run redis-cli "${@}"
}

test_str() {
	local key='name'

	cli SET ${key} \"Rong Tao\"
	cli GET ${key}
	cli MGET ${key}
	cli STRLEN ${key}
	cli APPEND ${key} \" is my name\"
	cli GET ${key}
	cli DEL ${key}
	cli GET ${key}

	cli SET ${key} \"Rong Tao\"
	cli GET ${key}
	cli GETRANGE ${key} 1 2
	cli UNLINK ${key}
}

test_int() {
	local key='score'

	cli SET ${key} 1

	cli INCR ${key}
	cli GET ${key}
	cli DECR ${key}
	cli GET ${key}

	cli INCRBY ${key} 10
	cli GET ${key}
	cli DECRBY ${key} 3
	cli GET ${key}

	cli INCRBYFLOAT ${key} 3.14
	cli GET ${key}

	cli DEL ${key}
}

test_timeout() {
	local key='anon'

	# SETEX key seconds value
	cli SETEX ${key} 1 1
	cli GET ${key}
	run sleep .5
	cli TTL ${key} # seconds
	cli PTTL ${key} # microseconds
	cli GET ${key}
	run sleep .6
	cli GET ${key}

	cli DEL ${key}

	# NX: not-exist
	cli SETNX ${key} rongtao
	cli GET ${key}
	cli DEL ${key}
	cli GET ${key}

	# Atomically implemented: set + expiration time only if it does not
	# exist
	# NX: not-exist
	cli SET ${key} rongtao NX EX 1
	run sleep .6
	cli TTL ${key}
	cli PTTL ${key}
	cli GET ${key}
	run sleep .6
	cli GET ${key}
}

test_str
test_int
test_timeout
