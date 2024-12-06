SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



TARGET=clock_gettime.out

all: ${TARGET}

clock_gettime.out:
	gcc clock_gettime.c -o clock_gettime.out

clean:
	rm -f ${TARGET}
