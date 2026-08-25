include cxl.mk

target-y += acpi0016
target-y += cedt

cedt-objs := chbs.o cfmws.o cxims.o rdpas.o

prog-${HAVE_CXL_DEVICE} += info.sh

CFLAGS := -I ../../libs/
