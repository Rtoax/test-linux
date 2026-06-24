#!/bin/bash
set -e

if [[ /etc/os-release -nt /etc/resolv.conf ]]; then
	echo newer
elif [[ /etc/os-release -ot /etc/resolv.conf ]]; then
	echo older
fi

if [[ __not_exist__ -nt __not_exist__ ]]; then
	echo "__not_exist__ newer"
elif [[ __not_exist__ -ot __not_exist__ ]]; then
	echo "__not_exist__ older"
else
	echo "__not_exist__ non newer neither older"
fi

if [[ /var/log/messages -nt /bin/ls ]]; then
	echo newer
else
	echo "FATAL: /var/log/messages should newer than /bin/ls"
	exit 1
fi
