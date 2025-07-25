CC := gcc

include ../../compiler.mk

targets += leak
targets += address
targets-cpp += address_cpp
targets += thread

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

ifdef LOCK
  CFLAGS := -DLOCK=1
else
  $(warning Define LOCK=1 to running with lock for SAN)
endif

include ../../../template/main.mk

address: address.o
address_cpp: address_cpp.cpp.o
leak: leak.o
thread: thread.o
