#!/bin/bash

if [[ -e /dev/vhost-net ]]; then
	echo "Found /dev/vhost-net"
	exit 0
fi

