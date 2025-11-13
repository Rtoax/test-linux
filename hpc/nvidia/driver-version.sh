#!/bin/bash
set -e

if  [[ -e /proc/driver/nvidia/version ]]; then
	cat /proc/driver/nvidia/version
fi
