include file.mk

prog-$(call fexist,/sys/firmware/acpi/tables) += iasl.sh
