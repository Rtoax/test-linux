# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

CXX := clang++

target-cpp-y += ParseCommandLineOptions
target-cpp-y += ParseCommandLineOptions-2
target-cpp-y += LLVM_VERSION_MAJOR

CXXFLAGS := -Wno-error=unused-command-line-argument
CXXFLAGS += $(shell llvm-config --cxxflags --system-libs --libs core mc mcjit ExecutionEngine)
LDXXFLAGS += $(shell llvm-config --ldflags --system-libs --libs core mc mcjit ExecutionEngine)

CXXFLAGS_ParseCommandLineOptions := -Wno-unused-command-line-argument
CXXFLAGS_ParseCommandLineOptions-2 := -Wno-unused-command-line-argument
