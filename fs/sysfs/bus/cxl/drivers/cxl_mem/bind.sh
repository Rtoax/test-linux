#!/bin/bash
# $ sudo create-region --decoder decoder0.0 --size 512M
#
# ....
# write "region0" to /sys/bus/cxl/drivers/cxl_port/bind
# write "region0" to /sys/bus/cxl/drivers/cxl_mem/bind
# write "region0" to /sys/bus/cxl/drivers/cxl_region/bind
set -e
