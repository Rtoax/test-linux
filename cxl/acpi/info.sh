#!/bin/bash
set -e

sudo dmesg | grep ACPI0017 || :

modinfo cxl_acpi

sudo acpidump > acpi.dat
sudo acpixtract -a acpi.dat
# Generate cedt.dat
if [[ -f cedt.dat ]]; then
	# Generate cedt.dsl
	sudo iasl -d cedt.dat
	cat cedt.dsl
fi

# CXL Root Port or Device on Switch
ls /sys/bus/acpi/devices/ACPI0017:*
# CXL Host Bridge
ls /sys/bus/acpi/devices/ACPI0016:*
