include llvm.mk

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

target-prep-y := ${SRCS}

target-libso-cpp-y := PrintFunctionNames.so
target-libso-cpp-y += AnnotateFunctions.so
target-libso-cpp-y += Attribute.so
target-libso-cpp-y += pid.so

target-post-y := test-plugins

PrintFunctionNames.so-objs := ${OUTPUT}PrintFunctionNames.cpp.so.o
AnnotateFunctions.so-objs := ${OUTPUT}AnnotateFunctions.cpp.so.o
Attribute.so-objs := ${OUTPUT}Attribute.cpp.so.o
pid.so-objs := ${OUTPUT}pid.cpp.so.o


include main.mk

${SRCS}:
	$(call log_tgt,COPY,$(@))
	${Q}cp ${clang-codes} $(shell pwd)

${OUTPUT}PrintFunctionNames.cpp.so.o: PrintFunctionNames.cpp
${OUTPUT}AnnotateFunctions.cpp.so.o: AnnotateFunctions.cpp
${OUTPUT}Attribute.cpp.so.o: Attribute.cpp
${OUTPUT}pid.cpp.so.o: pid.cpp

test-plugins:
	${Q}${SHELL} test-plugins.sh
