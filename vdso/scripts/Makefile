SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


all:
	gcc getauxval.c -o getauxval
clean:
	rm -f getauxval vDSO-VMA.out
