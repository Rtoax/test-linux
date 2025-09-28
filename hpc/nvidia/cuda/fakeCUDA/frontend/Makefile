# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

CXX := clang++

targets-libso-cpp += libfakecuda_plugin.so

include ../../../../../template/main.mk

${OUTPUT}lexerExtension.cpp.so.o: syntax.hpp

libfakecuda_plugin.so: ${OUTPUT}lexerExtension.cpp.so.o ${OUTPUT}attribute-device.cpp.so.o
