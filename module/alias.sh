#!/bin/bash
set -e

cat /lib/modules/$(uname -r)/modules.alias
sudo cat /sys/devices/{*,*/*,*/*/*}/modalias
