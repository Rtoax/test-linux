#!/bin/bash
set -e

run() {
	echo >&2 -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

run sudo dmesg | grep ACPI0017 || :

run modinfo cxl_acpi

run sudo acpidump > acpi.dat
run sudo acpixtract -a acpi.dat
# Generate cedt.dat
if [[ -f cedt.dat ]]; then
	# Generate cedt.dsl
	run sudo iasl -d cedt.dat
	run cat cedt.dsl
fi

LS=ls
[[ $(which find) ]] && LS=find
[[ $(which tree) ]] && LS=tree

run sudo ${LS} /sys/kernel/debug/cxl

# CXL Root Port or Device on Switch
# commit feaefb76110b ("cxl: acpi: list /sys/bus/acpi/devices/ACPI0017:*")
# commit 8f9edf13cfce ("cxl: acpi: list /sys/bus/acpi/devices/ACPI0017:00 on 5.15.131")
run sudo ${LS} /sys/bus/acpi/devices/ACPI0017:*
# commit c8687bc871c5 ("cxl: acpi: list /sys/devices/platform/ACPI0017:00/")
# commit 9de6cd3e6151 ("cxl: acpi: list /sys/devices/platform/ACPI0017:00 on 5.15.131")
run sudo ${LS} /sys/devices/platform/ACPI0017*
# CXL Host Bridge (CHBS: CXL Host Bridge Structure)
# commit 74c7dbaf1375 ("cxl: acpi: list /sys/bus/acpi/devices/ACPI0016:00 on 5.15.131")
run sudo ${LS} /sys/bus/acpi/devices/ACPI0016:*
