# SPDX-License-Identifier: GPL-3.0
include llvm.mk

CC := clang
CXX := clang++

target-libso-cpp-y += fakecuda_plugin.so

target-y := hello

plugin-objs := attribute-global.cpp.so.o
plugin-objs += attribute-device.cpp.so.o
plugin-objs += lexerExtension.cpp.so.o
fakecuda_plugin.so-objs := ${plugin-objs}

CFLAGS += -fplugin=./fakecuda_plugin.so
CXXFLAGS_SO += ${llvm-cflags}
