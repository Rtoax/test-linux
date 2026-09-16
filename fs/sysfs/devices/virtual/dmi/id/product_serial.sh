#!/bin/bash
set -e
# symlink /sys/devices/virtual/dmi/id/product_serial
# see also: sudo dmidecode -s system-serial-number
sudo cat /sys/class/dmi/id/product_serial
