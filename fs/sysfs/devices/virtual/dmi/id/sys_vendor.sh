#!/bin/bash
set -e
# symlink /sys/devices/virtual/dmi/id/sys_vendor
# see also: sudo dmidecode -t system
sudo cat /sys/class/dmi/id/sys_vendor
