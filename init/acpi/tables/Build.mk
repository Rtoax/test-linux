include file.mk

subdir-$(call file_exists,/sys/firmware/acpi/tables/CEDT) += cedt

target-y += bgrt
target-y += dsdt
target-y += srat

RUNPROG_ARGS += --maybe-sudo

prog-$(call file_exists,/sys/firmware/acpi/tables/BGRT) += bgrt
prog-$(call file_exists,/sys/firmware/acpi/tables/DSDT) += dsdt
prog-$(call file_exists,/sys/firmware/acpi/tables/SRAT) += srat
prog-$(call file_exists,/sys/firmware/acpi/tables) += iasl.sh
