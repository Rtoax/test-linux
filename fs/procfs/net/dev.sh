#!/bin/bash
set -e

# ifconfig's RX,TX packages, ...
# same as /proc/self/net/dev
cat /proc/net/dev

# Receive bytes is not zero
cat /proc/net/dev | awk '{
	if ($2 != 0) {
		printf($1"\n")
	}
}'
