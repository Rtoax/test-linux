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
${OUTPUT}attribute-global.cpp.so.o: configs.hpp
${OUTPUT}attribute-device.cpp.so.o: configs.hpp

plugin-objs := ${OUTPUT}attribute-global.cpp.so.o
plugin-objs += ${OUTPUT}attribute-device.cpp.so.o
plugin-objs += ${OUTPUT}lexerExtension.cpp.so.o

libfakecuda_plugin.so: ${plugin-objs}

hello: ${OUTPUT}hello.o
