include file.mk

subdir-$(call fexist,/sys/bus/cxl) += cxl
subdir-$(call fexist,/sys/bus/i2c) += i2c

prog-y += info.sh
