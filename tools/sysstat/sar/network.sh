#!/bin/bash
set -e

for iface in $(ls /sys/class/net/)
do
	sar -n ALL --iface=${iface}
done
