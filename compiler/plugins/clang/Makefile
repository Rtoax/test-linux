include ../../llvm/llvm.mk

OUTPUT := .output/

CC := clang
CXX := clang++

ifeq ($(wildcard ${CLANG_SRC_ROOT}),)
  $(error ERROR: ${CLANG_SRC_ROOT} is not exist)
endif

EXAMPLES_DIR := ${CLANG_SRC_ROOT}/examples

EXAMPLES_SRC := PrintFunctionNames.cpp

targets-prep := ${EXAMPLES_SRC}

targets-libso-cpp := PrintFunctionNames.so

targets-post := test-plugins


include ../../../template/main.mk

${EXAMPLES_SRC}:
	$(call log_tgt_obj,COPY,${EXAMPLES_DIR}PrintFunctionNames/$(@),$(@))
	${Q}cp ${EXAMPLES_DIR}/PrintFunctionNames/$(@) ${@}

${OUTPUT}PrintFunctionNames.cpp.so.o: PrintFunctionNames.cpp
PrintFunctionNames.so: ${OUTPUT}PrintFunctionNames.cpp.so.o

test-plugins:
	${Q}${SHELL} test-plugins.sh
