#!/bin/bash
set -e

printf "0-1023\n" > /tmp/fake_possible

cat /sys/devices/system/cpu/possible

fake_possible=$(sudo unshare -m bash -c \
	"mount --bind /tmp/fake_possible /sys/devices/system/cpu/possible && \
	exec cat /sys/devices/system/cpu/possible")
echo ${fake_possible}

if [[ ${fake_possible} != 0-1023 ]]; then
	exit 1
fi
