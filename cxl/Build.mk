include cxl.mk

subdir-y += acpi
subdir-y += bus

prog-${HAVE_CXL_DEVICES} += info.sh
