SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	gcc aesdec.c -maes -o aesdec

clean:
	rm -f aesdec *.out
