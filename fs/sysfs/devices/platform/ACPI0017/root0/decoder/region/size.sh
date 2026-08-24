#!/bin/bash
#
# $ sudo strace cxl create-region --decoder decoder0.0 --size 512M --type ram --memdevs mem0
#
# equal to:
#
# read 'region0' from /sys/bus/cxl/devices/root0/decoder0.0/create_ram_region
# write 'region0' to /sys/bus/cxl/devices/root0/decoder0.0/create_ram_region
# write 0x20000000 to /sys/bus/cxl/devices/root0/decoder0.0/region0/size
set -e

sudo cat /sys/bus/cxl/devices/root0/decoder0.0/region0/size
