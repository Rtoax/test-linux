include file.mk

subdir-$(call file_exists,/sys/bus/cxl/devices/mem0) += mem0
subdir-y += root0
