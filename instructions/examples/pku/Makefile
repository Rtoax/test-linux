targets :=
ifeq ($(shell uname -m),x86_64)
  targets += rdpkru
endif

include ../../../template/main.mk

rdpkru: rdpkru.o
