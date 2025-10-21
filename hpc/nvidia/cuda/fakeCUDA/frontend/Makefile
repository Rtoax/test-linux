# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

CC := clang
CXX := clang++

target-libso-cpp-y += fakecuda_plugin.so

test-exe := hello

target-y := ${test-exe}

CFLAGS += -fplugin=./fakecuda_plugin.so

include ../../../../../template/main.mk

${OUTPUT}hello.o: ${target-libso-cpp-y}

${OUTPUT}lexerExtension.cpp.so.o: syntax.hpp
${OUTPUT}attribute-global.cpp.so.o: configs.hpp
${OUTPUT}attribute-device.cpp.so.o: configs.hpp

plugin-objs := ${OUTPUT}attribute-global.cpp.so.o
plugin-objs += ${OUTPUT}attribute-device.cpp.so.o
plugin-objs += ${OUTPUT}lexerExtension.cpp.so.o

fakecuda_plugin.so: ${plugin-objs}

hello: ${OUTPUT}hello.o
