#!/bin/bash
set -e

console_tty=$(cat /sys/class/tty/console/active)
echo "console=\"${console_tty}\""

if [[ "${console_tty}" != "$(cat /sys/devices/virtual/tty/console/active)" ]]; then
	exit 1
fi
