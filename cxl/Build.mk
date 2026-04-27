include cxl.mk

subdir-y += acpi
subdir-y += bus

target-prog-${HAVE_CXL_DEVICES} += info.sh
