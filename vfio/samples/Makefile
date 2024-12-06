SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS += vfio_region_info

vfio_region_info: vfio_region_info.o

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *.o
