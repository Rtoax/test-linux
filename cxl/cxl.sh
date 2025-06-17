#!/bin/bash
set -e

# create region 0-3
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem0
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem1
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem2
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem3

# create region0
# will create /sys/bus/cxl/devices/region0
sudo cxl create-region --decoder decoder0.0 --size 4096M --type ram --memdevs mem0 mem1 mem2 mem3

sudo cxl enable-region region0
sudo cxl enable-region all
sudo cxl list --regions | jq .[].type

sudo cxl disable-region region0
sudo cxl destroy-region region0
