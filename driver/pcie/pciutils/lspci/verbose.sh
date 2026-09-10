#!/bin/bash
set -e

slot=0000:00:00.0

# see also
# - /sys/bus/pci/devices/${slot}/config
# - commit b70dac1a4b3e ("cxl: lspci: Capabilities: 4-ways pmem + 4-ways vmem + 4-ways vmem")
lspci -v -s ${slot}
lspci -vv -s ${slot}
lspci -vvv -s ${slot}
