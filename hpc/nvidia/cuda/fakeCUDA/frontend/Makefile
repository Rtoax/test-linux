# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

CC := clang
CXX := clang++

targets-libso-cpp += libfakecuda_plugin.so

test-exe := hello

targets := ${test-exe}

CFLAGS += -fplugin=./libfakecuda_plugin.so

include ../../../../../template/main.mk

${OUTPUT}hello.o: ${targets-libso-cpp}

${OUTPUT}lexerExtension.cpp.so.o: syntax.hpp

libfakecuda_plugin.so: ${OUTPUT}lexerExtension.cpp.so.o ${OUTPUT}attribute-device.cpp.so.o

hello: ${OUTPUT}hello.o
