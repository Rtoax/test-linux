include file.mk

target-y += acpi0016
target-y += cedt

cedt-objs := chbs.o cfmws.o cxims.o rdpas.o

prog-$(call fexist,/sys/bus/acpi/devices/ACPI0017:00) += info.sh

CFLAGS := -I ../../libs/
