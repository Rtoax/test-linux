include file.mk

subdir-$(call fexist, /sys/kernel/debug/cxl) += cxl
subdir-y += modules

prog-y += info.sh
