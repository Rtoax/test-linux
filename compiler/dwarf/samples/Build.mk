target-y := hello
target-post-y := hello.dwz hello.strip

target-clean-y := clean0

CFLAGS := -g
CFLAGS += -ggdb -O0
ifdef DWARF5
  CFLAGS += -gdwarf-5
else ifdef DWARF4
  CFLAGS += -gdwarf-4
endif

CFLAGS_hello += -Wno-error=unused-variable
