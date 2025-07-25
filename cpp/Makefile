# SPDX-License-Identifier: GPL-3.0
CXX := g++

include ../compiler/compiler.mk

OUTPUT := .output/

sub-dir := demangle

targets-cpp :=
targets-cpp += hello
targets-cpp += alignas
targets-cpp += extern_C
targets-cpp += pass-arg
targets-cpp += return
targets-cpp += this
targets-cpp += string
targets-cpp += __cplusplus
ifeq (${CC_STD_C++20},1)
  targets-cpp += format
endif
targets-cpp += fmt
targets-cpp += __STDC__ __STDC__c++98 __STDC__gnu++98
targets-cpp += expired

CXXFLAGS :=
CXXFLAGS += -DCPP

ifdef M32
  CXXFLAGS += -m32 -DM32=1
  CXXFLAGS += -m32 -DM32=1
  $(info Compile 32bit ELF)
endif

CXXFLAGS_return := -Wno-error=return-type
CXXFLAGS_format := -std=c++20
STD_FORMAT := '\#include <format>\n'
STD_FORMAT += '\#include <iostream>\n'
STD_FORMAT += 'int main(void) {\n'
STD_FORMAT += '	std::cout << std::format("{}_{}", "Hello", "World");\n'
STD_FORMAT += '	return 0;\n'
STD_FORMAT += '}'
define probe_std_format
  $(shell printf '%b\n' $(STD_FORMAT) | \
    $(CXX) -x c++ -Wall -Werror ${CXXFLAGS_format} - $(1) -S -o - >/dev/null 2>&1 \
      && echo y)
endef
has-std_format := $(findstring y,$(call probe_std_format))
ifeq ($(has-std_format),y)
  CXXFLAGS_format += -DSTD_FORMAT=1
endif
CXXFLAGS___STDC__c++98 := -std=c++98
CXXFLAGS___STDC__gnu++98 := -std=gnu++98
LDXXFLAGS_fmt := -lfmt

targets-post := $(addprefix ${OUTPUT},$(patsubst %,%.cpp.s,${targets-cpp}))

include ../template/main.mk

hello: ${OUTPUT}hello.cpp.o
alignas: ${OUTPUT}alignas.cpp.o
extern_C: ${OUTPUT}extern_C.cpp.o
pass-arg: ${OUTPUT}pass-arg.cpp.o
return: ${OUTPUT}return.cpp.o
this: ${OUTPUT}this.cpp.o
string: ${OUTPUT}string.cpp.o
__cplusplus: ${OUTPUT}__cplusplus.cpp.o
__STDC__: ${OUTPUT}__STDC__.cpp.o
__STDC__c++98: ${OUTPUT}__STDC__c++98.cpp.o
__STDC__gnu++98: ${OUTPUT}__STDC__gnu++98.cpp.o
format: ${OUTPUT}format.cpp.o
fmt: ${OUTPUT}fmt.cpp.o
expired: ${OUTPUT}expired.cpp.o
