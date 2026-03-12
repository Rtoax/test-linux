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

target-prog-y := $(shell ls *.sh)

CFLAGS += -O0 -ggdb
LDFLAGS += -pthread

CXXFLAGS += -O0 -ggdb
LDXXFLAGS += -pthread

CFLAGS_hello := -Wno-error=unused-function
