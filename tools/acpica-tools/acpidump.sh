#!/bin/bash
# /sys/firmware/acpi/tables/
set -e

# Save to binary
sudo acpidump -b

# Display to stdout
sudo acpidump > acpi.txt
sudo acpixtract -l acpi.txt
sudo acpixtract -a acpi.txt
