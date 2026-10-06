#!/bin/bash
set -e

cli() {
	echo -e "\033[1;32m${@}\033[m"
	eval "redis-cli "${@}""
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

test_str
test_int
