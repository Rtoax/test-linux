SHELL = bash
include ../../tlbuild.mk


TARGETS += vfio_region_info

vfio_region_info: vfio_region_info.o

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *.o
