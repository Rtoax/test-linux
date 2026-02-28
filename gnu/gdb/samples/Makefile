OUTPUT := .output/

target-y += set-value
target-y += set-value-func
target-y += set-value-volatile
target-y += pthread-gdb
target-y += hello
target-y += fork
target-y += linklist
target-y += daxpy

target-cpp-y := global-var

target-prep-y := hello.strip

target-shell-y := $(shell ls *.sh)

CFLAGS += -O0 -ggdb
LDFLAGS += -pthread

CXXFLAGS += -O0 -ggdb
LDXXFLAGS += -pthread

CFLAGS_hello := -Wno-error=unused-function

include main.mk

fork: ${OUTPUT}fork.o
set-value: ${OUTPUT}set-value.o
set-value-func: ${OUTPUT}set-value-func.o
set-value-volatile: ${OUTPUT}set-value-volatile.o
pthread-gdb: ${OUTPUT}pthread-gdb.o
hello: ${OUTPUT}hello.o
linklist: ${OUTPUT}linklist.o
daxpy: ${OUTPUT}daxpy.o
global-var: ${OUTPUT}global-var.cpp.o

# Strip
hello.strip: hello

# The following two commands same as
#  @eu-strip hello -f hello.debug -o hello.strip
define mystrip
	@objcopy --only-keep-debug $(1) $(1).debug
	$(Q)strip $(1) -o $(1).strip
endef

%.strip:
	$(call log_tgt,STRIP,$(@))
	$(call mystrip,$(^))
