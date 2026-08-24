include cxl.mk

subdir-y += acpi
subdir-y += bus
subdir-y += fm

prog-${HAVE_CXL_DEVICE} += info.sh
