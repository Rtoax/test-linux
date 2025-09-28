include ../../llvm/llvm.mk

OUTPUT := .output/

CC := clang
CXX := clang++

ifeq ($(wildcard ${CLANG_SRC_ROOT}),)
  $(error ERROR: ${CLANG_SRC_ROOT} is not exist)
endif

clang-codes := ${CLANG_SRC_ROOT}/examples/PrintFunctionNames/PrintFunctionNames.cpp
clang-codes += ${CLANG_SRC_ROOT}/examples/AnnotateFunctions/AnnotateFunctions.cpp
clang-codes += ${CLANG_SRC_ROOT}/examples/Attribute/Attribute.cpp

SRCS := $(notdir $(clang-codes))

targets-prep := ${SRCS}

targets-libso-cpp := PrintFunctionNames.so
targets-libso-cpp += AnnotateFunctions.so
targets-libso-cpp += Attribute.so

targets-post := test-plugins


include ../../../template/main.mk

${SRCS}:
	$(call log_tgt_obj,COPY,,$(@))
	${Q}cp ${clang-codes} $(shell pwd)

${OUTPUT}PrintFunctionNames.cpp.so.o: PrintFunctionNames.cpp
PrintFunctionNames.so: ${OUTPUT}PrintFunctionNames.cpp.so.o

${OUTPUT}AnnotateFunctions.cpp.so.o: AnnotateFunctions.cpp
AnnotateFunctions.so: ${OUTPUT}AnnotateFunctions.cpp.so.o

${OUTPUT}Attribute.cpp.so.o: Attribute.cpp
Attribute.so: ${OUTPUT}Attribute.cpp.so.o

test-plugins:
	${Q}${SHELL} test-plugins.sh
