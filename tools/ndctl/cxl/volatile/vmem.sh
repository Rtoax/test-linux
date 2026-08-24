#!/bin/bash
set -e
# commit d5a21a914482 ("cxl.sh: multi memdevs to on region")

# create region0, commit b3c049d89aa9 ("cxl: cxl.sh: create-region")
# will create
# - /sys/bus/cxl/devices/region0/dax_region
# - /sys/devices/platform/ACPI0017:00/root0/decoder0.0/region0/dax_region0/dax0.0
# - /sys/bus/dax/devices/dax0.0
# - /sys/bus/dax/drivers/kmem/dax0.0
# - /dev/dax0.0 [Character Device], commit 1227030c1d3f ("cxl.sh: region: character device /dev/dax0.0")
sudo cxl create-region --decoder decoder0.0 --size 4096M --type ram --memdevs mem0 mem1 mem2 mem3
# or only use one way
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem0

sudo cxl enable-region region0
sudo cxl enable-region all
sudo cxl list --regions | jq '.[].type'

sudo daxctl list
sudo daxctl list -r region0

# add memory to main RAM
# commit 21535dd38b6e ("cxl: dax0.0: use as system-ram")
free -g
sudo daxctl online-memory dax0.0

# Use CXL System RAM...
free -g

sudo daxctl offline-memory dax0.0
free -g

sudo cxl disable-region region0
sudo cxl destroy-region region0
