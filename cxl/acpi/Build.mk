include cxl.mk

target-y := cedt
cedt-objs := chbs.o cfmws.o

prog-${HAVE_CXL_DEVICES} += info.sh

CFLAGS := -I ../../libs/
