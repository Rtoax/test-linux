CC := gcc

include ../../compiler.mk

TARGETS += fsanitize
TARGETS += leak
TARGETS_CPP += fsanitize_cpp

# Depends on libasan
CFLAGS_fsanitize := -fsanitize=address
ifneq ($(CC),clang)
  CFLAGS_fsanitize += -Wno-error=stringop-overflow
endif
LDFLAGS_fsanitize := ${CFLAGS_fsanitize} -lasan

CFLAGS_leak := -fsanitize=leak
LDFLAGS_leak := -llsan

CXXFLAGS_fsanitize_cpp := ${CFLAGS_fsanitize}
CXXFLAGS_fsanitize_cpp += -Wno-error=stringop-overflow
LDXXFLAGS_fsanitize_cpp := ${LDFLAGS_fsanitize} -lasan

include ../../../template/main.mk

fsanitize: fsanitize.o
fsanitize_cpp: fsanitize_cpp.opp
leak: leak.o
