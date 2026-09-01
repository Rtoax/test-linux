include file.mk

subdir-$(call fexist, /sys/kernel/debug/cxl) += cxl
subdir-y += modules
subdir-y += tracing

prog-y += info.sh
