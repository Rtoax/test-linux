#!/bin/bash
set -e

if [[ -z "$(sudo systemctl status redis.service | \
		grep -o 'Active: active' 2>/dev/null)" ]] ||
   [[ -z "$(pidof valkey-server)$(pidof redis-server)" ]]; then
	echo "WARNING: Not found redis server, skipping"
	exit 0
fi

redis-cli ping
