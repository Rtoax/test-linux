#!/bin/bash
set -e

ls /sys/firmware/acpi/

sudo acpidump > acpi.dat
sudo acpixtract -a acpi.dat
