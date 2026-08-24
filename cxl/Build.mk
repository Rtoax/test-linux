include cxl.mk

subdir-${HAVE_CXL_DEVICE} += acpi
subdir-${HAVE_CXL_DEVICE} += bus
subdir-y += fm

prog-${HAVE_CXL_DEVICE} += info.sh
