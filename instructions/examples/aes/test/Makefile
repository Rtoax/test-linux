SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	gcc -o main main.c sm4_aesni_x4.c sm4.c -Og -msse4 -maes
clean:
	rm -f main
