#!/bin/bash
set -e

# create region0
# will create
# - /sys/bus/cxl/devices/region0/dax_region
# - /sys/devices/platform/ACPI0017:00/root0/decoder0.0/region0/dax_region0/dax0.0
# - /sys/bus/dax/devices/dax0.0
# - /sys/bus/dax/drivers/kmem/dax0.0
# - /dev/dax0.0 [Character Device]
sudo cxl create-region --decoder decoder0.0 --size 4096M --type ram --memdevs mem0 mem1 mem2 mem3

sudo cxl enable-region region0
sudo cxl enable-region all
sudo cxl list --regions | jq .[].type

sudo daxctl list
sudo daxctl list -r region0
sudo daxctl online-memory dax0.0
sudo daxctl offline-memory dax0.0

sudo cxl disable-region region0
sudo cxl destroy-region region0
