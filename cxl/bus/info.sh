#!/bin/bash
set -e

if [[ ! -d /sys/bus/cxl/ ]]; then
	exit 0
fi

ls /sys/bus/cxl/
