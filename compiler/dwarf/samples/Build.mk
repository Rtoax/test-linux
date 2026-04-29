target-y += hello
target-y += hello.dw4
target-y += hello.dw5

target-post-y := hello.dwz hello.strip

target-clean-y := clean0

hello.dw4-objs := hello.1.o
hello.dw5-objs := hello.2.o

CFLAGS := -g
CFLAGS += -ggdb -O0

CFLAGS_hello += -Wno-error=unused-variable
CFLAGS_hello.1 += ${CFLAGS_hello} -gdwarf-4
CFLAGS_hello.2 += ${CFLAGS_hello} -gdwarf-5
