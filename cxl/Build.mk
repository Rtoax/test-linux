include cxl.mk
subdir-y := acpi

target-prog-${HAVE_CXL_DEVICES} += info.sh
