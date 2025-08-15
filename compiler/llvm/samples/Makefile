# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

CXX := clang++

targets-cpp :=
targets-cpp += ParseCommandLineOptions
targets-cpp += ParseCommandLineOptions-2
targets-cpp += LLVM_VERSION_MAJOR

CXXFLAGS := -Wno-error=unused-command-line-argument
CXXFLAGS += $(shell llvm-config --cxxflags --system-libs --libs core mc mcjit ExecutionEngine)
LDXXFLAGS += $(shell llvm-config --ldflags --system-libs --libs core mc mcjit ExecutionEngine)

CXXFLAGS_ParseCommandLineOptions := -Wno-unused-command-line-argument
CXXFLAGS_ParseCommandLineOptions-2 := -Wno-unused-command-line-argument

include ../../../template/main.mk

ParseCommandLineOptions: ${OUTPUT}ParseCommandLineOptions.cpp.o
ParseCommandLineOptions-2: ${OUTPUT}ParseCommandLineOptions-2.cpp.o
LLVM_VERSION_MAJOR: ${OUTPUT}LLVM_VERSION_MAJOR.cpp.o
