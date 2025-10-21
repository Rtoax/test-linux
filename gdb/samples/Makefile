target-y :=
target-y += set-value
target-y += set-value-func
target-y += set-value-volatile
target-y += pthread-gdb
target-y += hello
target-y += linklist
target-y += daxpy

target-cpp-y := global-var

target-prep-y := hello.strip

target-shell-y := $(shell ls *.sh)

CFLAGS :=
CFLAGS += -O0 -ggdb
LDFLAGS += -pthread

CXXFLAGS :=
CXXFLAGS += -O0 -ggdb
LDXXFLAGS += -pthread

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
	$(Q)strip $(1) -o $(1).strip
endef

%.strip:
	$(call log_tgt_exe,STRIP,$(^),$(^).strip)
	$(call mystrip,$(^))
