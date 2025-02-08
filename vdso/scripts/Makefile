SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

all:
	${Q}gcc getauxval.c -o getauxval
clean:
	${Q}rm -f getauxval vDSO-VMA.out
