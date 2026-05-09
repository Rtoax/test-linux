#!/bin/bash
set -e

if [[ -z "$(sudo systemctl status redis.service | \
		grep -o 'Active: active' 2>/dev/null)" ]] ||
   [[ -z "$(pidof valkey-server)$(pidof redis-server)" ]]; then
	echo "WARNING: Try (re)start redis server..."
	sudo systemctl start redis.service
fi
