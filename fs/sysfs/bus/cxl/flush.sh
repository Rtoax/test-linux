#!/bin/bash
set -e

if [[ ! -d /sys/bus/cxl/ ]]; then
	exit 0
fi

echo 1 | sudo tee /sys/bus/cxl/flush
