#!/bin/bash
#
# sudo cxl disable-region region0
#
# equal to:
#
# write 'region0' to /sys/bus/cxl/devices/root0/decoder0.0/region0/driver/unbind
set -e

if ! [[ -e /sys/bus/cxl/devices/root0/decoder0.0/region0/driver/unbind ]]; then
	exit 1
fi
