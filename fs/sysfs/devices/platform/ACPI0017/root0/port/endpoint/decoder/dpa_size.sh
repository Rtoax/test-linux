#!/bin/bash
# DPA: CXL Memory Device Physical Address
#
# $ sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem0
# write "1024M" to /sys/bus/cxl/devices/root0/port1/endpoint2/decoder2.0/dpa_size
#
# $ sudo cxl destroy-region region0
# write "0"     to /sys/bus/cxl/devices/root0/port1/endpoint2/decoder2.0/dpa_size
#
set -e
