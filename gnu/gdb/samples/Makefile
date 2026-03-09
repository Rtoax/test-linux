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
