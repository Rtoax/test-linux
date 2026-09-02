#!/bin/bash
# DSDT: commit 8e162de96d50 ("acpi: parse DSDT use iasl (with CXL _OSC)")
set -e

for table in $(find /sys/firmware/acpi/tables/ -maxdepth 1 -type f)
do
	echo "${table}"
	name=$(basename ${table})
	sudo iasl -p ${name} -d ${table}
done
