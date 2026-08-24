include file.mk

subdir-$(call fexist,/sys/bus/cxl/devices/root0/decoder0.0/region0) += region

prog-y += create_ram_region.sh
prog-y += devtype.sh
