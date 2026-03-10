# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

include llvm.mk

CC := clang
CXX := clang++

target-libso-cpp-y += fakecuda_plugin.so

target-y := hello

plugin-objs := ${OUTPUT}attribute-global.cpp.so.o
plugin-objs += ${OUTPUT}attribute-device.cpp.so.o
plugin-objs += ${OUTPUT}lexerExtension.cpp.so.o
fakecuda_plugin.so-objs := ${plugin-objs}

CFLAGS += -fplugin=./fakecuda_plugin.so
CXXFLAGS_SO += ${llvm-cflags}

include main.mk
