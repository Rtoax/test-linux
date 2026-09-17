#!/bin/bash
# Lazy deletion
set -e

cli() {
	redis-cli "$@"
}

key="names"

cli RPUSH ${key} "rongtao" "lihaiqiang"

cli EXPIRE ${key} 5
cli TTL ${key}
cli PTTL ${key}
cli PERSIST ${key}

cli DEL ${key}
