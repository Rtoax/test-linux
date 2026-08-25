#!/bin/bash
# $ sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem0
# write "decoder2.0" to /sys/bus/cxl/devices/root0/decoder0.0/region0/target0
#
# $ sudo cxl destroy-region region0
# write "" to /sys/bus/cxl/devices/root0/decoder0.0/region0/target0
set -e

sudo cat /sys/bus/cxl/devices/root0/decoder0.0/region0/target0
