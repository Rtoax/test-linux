#!/bin/bash
set -e

for table in $(find /sys/firmware/acpi/tables/ -maxdepth 1 -type f)
do
	echo "${table}"
	name=$(basename ${table})
	sudo iasl -p ${name} -d ${table}
done
