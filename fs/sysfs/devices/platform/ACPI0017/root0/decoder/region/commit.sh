#!/bin/bash
# $ sudo strace cxl create-region --decoder decoder0.0 --size 512M --type ram --memdevs mem0
# write "1" to /sys/bus/cxl/devices/root0/decoder0.0/region0/commit
#
# $ sudo cxl destroy-region region0
# write "0" to /sys/bus/cxl/devices/root0/decoder0.0/region0/commit
set -e

sudo cat /sys/bus/cxl/devices/root0/decoder0.0/region0/commit
