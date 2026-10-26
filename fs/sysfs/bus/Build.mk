include file.mk

subdir-$(call file_exists,/sys/bus/cxl) += cxl
subdir-$(call file_exists,/sys/bus/i2c) += i2c

prog-y += info.sh
