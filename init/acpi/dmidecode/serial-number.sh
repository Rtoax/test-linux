#!/bin/bash
set -e

sudo dmidecode | grep 'Serial Number'

# see also: /sys/class/dmi/id/product_serial
sudo dmidecode -s system-serial-number
