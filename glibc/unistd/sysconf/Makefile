targets := NPROCESSORS
targets += PAGESIZE
targets += sysconf

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | sed 's/"//g')

CFLAGS :=

LDFLAGS :=

ifdef STATIC
  CFLAGS += -static
  MAKEFLAGS += STATIC=1
  $(info Defined STATIC)
endif

CFLAGS_NPROCESSORS := -D_NPROCESSORS=1
LDFLAGS_NPROCESSORS :=
CFLAGS_sysconf := -Wno-error

targets-prep := confs_def.h
targets-clean := cleans

include ../../../template/main.mk

confs_def.h: sysconf.sh
	$(shell bash sysconf.sh)

NPROCESSORS: NPROCESSORS.o
PAGESIZE: PAGESIZE.o
sysconf: sysconf.o

cleans:
	${Q}rm -f gen-sysconf-* confs_def.h
