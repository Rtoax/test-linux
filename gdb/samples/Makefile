TARGETS :=
TARGETS += set-value
TARGETS += set-value-func
TARGETS += set-value-volatile
TARGETS += pthread-gdb
TARGETS += hello
TARGETS += linklist
TARGETS += daxpy

TARGETS_PREP := hello.strip

TARGETS_CPP := global-var

TARGETS_SHELL := $(shell ls *.sh)

CFLAGS :=
CFLAGS += -O0 -ggdb
CFLAGS += -pthread

CXXFLAGS :=
CXXFLAGS += -O0 -ggdb

ifneq ($(PIE),)
  CFLAGS += -fpie
  LDFLAGS += -pie
  CXXFLAGS += -fpie
endif

CFLAGS_hello := -Wno-error=unused-function

include ../../template/main.mk

set-value: set-value.o
set-value-func: set-value-func.o
set-value-volatile: set-value-volatile.o
pthread-gdb: pthread-gdb.o
hello: hello.o
linklist: linklist.o
daxpy: daxpy.o
global-var: global-var.cpp.o

# Strip
hello.strip: hello

# The following two commands same as
#  @eu-strip hello -f hello.debug -o hello.strip
define mystrip
	@objcopy --only-keep-debug $(1) $(1).debug
	@strip $(1) -o $(1).strip
endef

%.strip:
	@echo -e "  STRIP  \033[1;32m$(@)\033[m"
	$(call mystrip,$(^))
