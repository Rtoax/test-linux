include file.mk

HAVE_ACPI_TABLES := $(call fexist,/sys/firmware/acpi/tables)

prog-y += acpidump.sh
prog-${HAVE_ACPI_TABLES} += iasl.sh
