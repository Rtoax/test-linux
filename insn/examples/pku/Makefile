target-y :=
ifeq ($(shell uname -m),x86_64)
  target-y += rdpkru
endif

include main.mk

rdpkru: rdpkru.o
