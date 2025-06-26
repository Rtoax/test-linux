# SPDX-License-Identifier: GPL-3.0
TARGETS_CPP :=
TARGETS_CPP += ParseCommandLineOptions
TARGETS_CPP += ParseCommandLineOptions-2
TARGETS_CPP += LLVM_VERSION_MAJOR

CLANG_CXX := $(shell which clang++ 2>/dev/null)
ifneq ($(wildcard $(CLANG_CXX)),)
  CXX := ${CLANG_CXX}
else
  $(warning "WARNING: not found clang++")
  CXX := c++
endif

ifeq ($(CXX),)
  $(warning Not found ${CXX}, please install first)
endif

CXXFLAGS :=
CXXFLAGS += -Wno-error=unused-command-line-argument
CXXFLAGS += $(shell llvm-config --cxxflags --system-libs --libs core mc mcjit ExecutionEngine)
LDXXFLAGS += $(shell llvm-config --ldflags --system-libs --libs core mc mcjit ExecutionEngine)

CXXFLAGS_ParseCommandLineOptions := -Wno-unused-command-line-argument
CXXFLAGS_ParseCommandLineOptions-2 := -Wno-unused-command-line-argument

include ../../../template/main.mk

ParseCommandLineOptions: ParseCommandLineOptions.cpp.o
ParseCommandLineOptions-2: ParseCommandLineOptions-2.cpp.o
LLVM_VERSION_MAJOR: LLVM_VERSION_MAJOR.cpp.o
