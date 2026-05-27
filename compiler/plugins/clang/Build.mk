include llvm.mk

CC := clang
CXX := clang++

ifeq ($(wildcard ${CLANG_SRC_ROOT}),)
  $(error ERROR: ${CLANG_SRC_ROOT} is not exist)
endif

clang-codes := ${CLANG_SRC_ROOT}/examples/PrintFunctionNames/PrintFunctionNames.cpp
clang-codes += ${CLANG_SRC_ROOT}/examples/AnnotateFunctions/AnnotateFunctions.cpp
clang-codes += ${CLANG_SRC_ROOT}/examples/Attribute/Attribute.cpp

SRCS := $(notdir $(clang-codes))

target-prep-y := ${SRCS}

target-libso-cpp-y := PrintFunctionNames.so
target-libso-cpp-y += AnnotateFunctions.so
target-libso-cpp-y += Attribute.so
target-libso-cpp-y += pid.so

prog-y := test-plugins.sh

PrintFunctionNames.so-objs := PrintFunctionNames.cpp.so.o
AnnotateFunctions.so-objs := AnnotateFunctions.cpp.so.o
Attribute.so-objs := Attribute.cpp.so.o
pid.so-objs := pid.cpp.so.o
