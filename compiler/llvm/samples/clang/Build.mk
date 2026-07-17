# SPDX-License-Identifier: GPL-3.0
CXX := clang++

target-cpp-y += CompilerInstance

CXXFLAGS += -Wno-error=unused-command-line-argument
CXXFLAGS += $(shell llvm-config --cxxflags --system-libs --libs core)
LDXXFLAGS += $(shell llvm-config --ldflags --system-libs --libs core)
