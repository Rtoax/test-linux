include file.mk

subdir-$(call fexist,/sys/bus/cxl/devices/mem0) += mem0
subdir-y += root0
