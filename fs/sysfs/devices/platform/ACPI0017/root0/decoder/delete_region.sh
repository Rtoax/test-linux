#!/bin/bash
#
# $ sudo cxl destroy-region region0
# write 'region0' to /sys/bus/cxl/devices/root0/decoder0.0/delete_region
set -e

if ! [[ -e /sys/bus/cxl/devices/root0/decoder0.0/delete_region ]]; then
	exit 1
fi
