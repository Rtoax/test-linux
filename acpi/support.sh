#!/bin/bash

acpi_support=$(sudo dmidecode | grep -i 'ACPI is supported')
if [[ ! -z ${acpi_support} ]]; then
	echo "ACPI: Support"
else
	echo "ACPI: Unsupport"
fi
