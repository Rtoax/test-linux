#!/bin/bash

if [[ -e /dev/vhost-net ]]; then
	echo "You are in vhost-net guest OS"
	exit 0
fi

