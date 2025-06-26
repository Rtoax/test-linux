CC := gcc

include ../../compiler.mk

TARGETS += leak
TARGETS += address
TARGETS_CPP += address_cpp

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


include ../../../template/main.mk

address: address.o
address_cpp: address_cpp.opp
leak: leak.o
