#!/bin/bash
set -e

# /usr/lib/systemd/system/valkey.service
if [[ -e /usr/lib/systemd/system/redis.service ]]; then
	SERVICE=redis.service
elif [[ -e /usr/lib/systemd/system/redis-server.service ]]; then
	SERVICE=redis-server.service
else
	echo >&2 "ERROR: not found redis systemd service"
	exit 1
fi


if [[ -z "$(sudo systemctl status ${SERVICE} | \
		grep -o 'Active: active' 2>/dev/null)" ]] ||
   [[ -z "$(pidof valkey-server)$(pidof redis-server)" ]]; then
	echo "WARNING: Try (re)start redis server..."
	sudo systemctl start ${SERVICE}
fi
