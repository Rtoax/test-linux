include file.mk

subdir-$(call file_exists, /sys/kernel/debug/cxl) += cxl
subdir-y += modules
subdir-y += tracing

prog-y += info.sh
