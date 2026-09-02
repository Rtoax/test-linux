include file.mk

subdir-$(call fexist,/sys/firmware/acpi/tables/CEDT) += cedt

target-y += bgrt
target-y += dsdt

RUNPROG_ARGS += --maybe-sudo

prog-$(call fexist,/sys/firmware/acpi/tables/DSDT) += dsdt
prog-$(call fexist,/sys/firmware/acpi/tables) += iasl.sh
