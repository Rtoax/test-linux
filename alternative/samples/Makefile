targets :=

ifeq ($(shell uname -m),x86_64)
  targets += macro
else
  $(warning Not support arch except x86_64)
endif

include ../../template/main.mk

macro: macro.o
