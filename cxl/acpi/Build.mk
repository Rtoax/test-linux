include file.mk

target-y += acpi0016
target-y += cedt

cedt-objs := chbs.o cfmws.o cxims.o rdpas.o

prog-$(call fexist,/sys/bus/acpi/devices/ACPI0017:00) += info.sh
prog-$(call fexist,/sys/firmware/acpi/tables/DSDT) += acpi0016
prog-$(call fexist,/sys/firmware/acpi/tables/CEDT) += cedt

RUNPROG_ARGS := --maybe-sudo

CFLAGS := -I ../../libs/
