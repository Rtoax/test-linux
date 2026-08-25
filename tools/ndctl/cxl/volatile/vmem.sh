#!/bin/bash
set -e
# commit d5a21a914482 ("cxl.sh: multi memdevs to on region")

# Create region0, commit b3c049d89aa9 ("cxl: cxl.sh: create-region")
#
# Create:
# - /sys/bus/cxl/devices/region0/dax_region
# - /sys/devices/platform/ACPI0017:00/root0/decoder0.0/region0/dax_region0/dax0.0
# - /sys/bus/dax/devices/dax0.0
# - /sys/bus/dax/drivers/kmem/dax0.0
# - /dev/dax0.0 [Character Device], commit 1227030c1d3f ("cxl.sh: region: character device /dev/dax0.0")
#
# Write:
# - "region0"  to /sys/bus/cxl/devices/root0/decoder0.0/create_ram_region
# - 256        to /sys/bus/cxl/devices/root0/decoder0.0/region0/interleave_granularity
# - 1          to /sys/bus/cxl/devices/root0/decoder0.0/region0/interleave_ways
# - 1024M      to /sys/bus/cxl/devices/root0/decoder0.0/region0/size
# - 1024M      to /sys/bus/cxl/devices/root0/port1/endpoint2/decoder2.0/dpa_size
# - decoder2.0 to /sys/bus/cxl/devices/root0/decoder0.0/region0/target0
# - 1          to /sys/bus/cxl/devices/root0/decoder0.0/region0/commit
# - "region0"  to /sys/bus/cxl/drivers/cxl_port/bind
# - "region0"  to /sys/bus/cxl/drivers/cxl_mem/bind
# - "region0"  to /sys/bus/cxl/drivers/cxl_region/bind
sudo cxl create-region --decoder decoder0.0 --size 4096M --type ram --memdevs mem0 mem1 mem2 mem3
# Or only use way
sudo cxl create-region --decoder decoder0.0 --size 1024M --type ram --memdevs mem0

sudo cxl enable-region region0
sudo cxl enable-region all
sudo cxl list --regions | jq '.[].type'

sudo daxctl list
sudo daxctl list -r region0

# Add memory to main RAM
# commit 21535dd38b6e ("cxl: dax0.0: use as system-ram")
free -g
sudo daxctl online-memory dax0.0

# Use CXL System RAM...
free -g

sudo daxctl offline-memory dax0.0
free -g

# Disable region0
#
# Write:
# - "region0"   to /sys/bus/cxl/devices/root0/decoder0.0/region0/driver/unbind
sudo cxl disable-region region0

# Destroy region0
#
# Write:
# - 0         to /sys/bus/cxl/devices/root0/decoder0.0/region0/commit
# - ""        to /sys/bus/cxl/devices/root0/decoder0.0/region0/target0
# - 0         to /sys/bus/cxl/devices/root0/port1/endpoint2/decoder2.0/dpa_size
# - "region0" to /sys/bus/cxl/devices/root0/decoder0.0/delete_region
sudo cxl destroy-region region0
