#!/bin/bash
# DPA: CXL Memory Device Physical Address
set -e

sudo cat /sys/kernel/debug/cxl/mem0/dpamem
