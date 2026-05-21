#!/bin/bash
set -e

cli() {
	redis-cli "$@"
}

key="names"

cli RPUSH ${key} "rongtao" "lihaiqiang"

cli EXPIRE ${key} 5

cli PERSIST ${key}

cli DEL ${key}
