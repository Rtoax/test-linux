include file.mk

subdir-y += block
subdir-y += cpu
subdir-$(call file_exists,/dev/cxl) += cxl
subdir-y += input
subdir-y += kmsg
subdir-y += loop
subdir-y += random
