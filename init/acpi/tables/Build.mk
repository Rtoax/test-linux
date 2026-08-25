include file.mk
subdir-y += cxl

target-y += bgrt
target-y += dsdt

RUNPROG_ARGS += --maybe-sudo

prog-$(call fexist,/sys/firmware/acpi/tables/DSDT) += dsdt
