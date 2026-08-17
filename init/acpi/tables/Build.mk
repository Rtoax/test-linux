include file.mk

target-y += bgrt
target-y += dsdt

RUNPROG_ARGS += --maybe-sudo

prog-$(call fexist,/sys/firmware/acpi/tables/DSDT) += dsdt
