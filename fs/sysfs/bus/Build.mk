include file.mk

subdir-$(call fexist,/sys/bus/cxl) += cxl

prog-y += info.sh
