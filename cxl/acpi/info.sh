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

sudo ls /sys/kernel/debug/cxl

# CXL Root Port or Device on Switch
sudo ls /sys/bus/acpi/devices/ACPI0017:*
# commit c8687bc871c5 ("cxl: list /sys/devices/platform/ACPI0017:00/")
sudo ls /sys/devices/platform/ACPI0017*
# CXL Host Bridge (CHBS: CXL Host Bridge Structure)
sudo ls /sys/bus/acpi/devices/ACPI0016:*
