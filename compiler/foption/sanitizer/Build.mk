include compiler.mk

target-y += address
target-cpp-y += address_cpp
target-y += leak
target-y += thread
target-y += undefined
target-y += uninitialized-member

# Depends on libasan
CFLAGS_address := -fsanitize=address
ifneq ($(CC),clang)
  CFLAGS_address += -Wno-error=stringop-overflow
endif
LDFLAGS_address := -lasan

CXXFLAGS_address_cpp := ${CFLAGS_address}
CXXFLAGS_address_cpp += -Wno-error=stringop-overflow
LDXXFLAGS_address_cpp := ${LDFLAGS_address}

CFLAGS_leak := -fsanitize=leak
LDFLAGS_leak := -llsan

CFLAGS_thread := -fsanitize=thread
LDFLAGS_thread := -ltsan -pthread

CFLAGS_undefined := -fsanitize=undefined
LDFLAGS_undefined := -lasan

CFLAGS_uninitialized-member := -fsanitize=address -fsanitize=undefined
LDFLAGS_uninitialized-member := -lasan -lubsan

ifdef LOCK
  CFLAGS := -DLOCK=1
else
  $(warning Define LOCK=1 to running with lock for SAN)
endif
