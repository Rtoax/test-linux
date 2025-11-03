# SPDX-License-Identifier: GPL-3.0
CXX := g++

include ../compiler/compiler.mk

OUTPUT := .output/

subdir-y := demangle

target-cpp-y :=
target-cpp-y += hello
target-cpp-y += alignas
target-cpp-y += extern_C
target-cpp-y += pass-arg
target-cpp-y += return
target-cpp-y += this
target-cpp-y += string
target-cpp-y += __cplusplus
target-cpp-${CC_STD_C++20} += format
target-cpp-y += fmt
target-cpp-y += __STDC__
target-cpp-y += __STDC__c++98 __STDC__gnu++98
target-cpp-y += __STDC__c++03
target-cpp-y += __STDC__c++11
target-cpp-y += __STDC__c++14
target-cpp-y += __STDC__c++17
target-cpp-y += __STDC__c++20
target-cpp-y += __STDC__c++23
target-cpp-y += expired

CXXFLAGS :=
CXXFLAGS += -DCPP

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
CXXFLAGS___STDC__c++03 := -std=c++03
CXXFLAGS___STDC__c++11 := -std=c++11
CXXFLAGS___STDC__c++14 := -std=c++14
CXXFLAGS___STDC__c++17 := -std=c++17
CXXFLAGS___STDC__c++20 := -std=c++20
CXXFLAGS___STDC__c++23 := -std=c++23
LDXXFLAGS_fmt := -lfmt

target-post-y := $(addprefix ${OUTPUT},$(patsubst %,%.cpp.s,${target-cpp-y}))

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
__STDC__c++03: ${OUTPUT}__STDC__c++03.cpp.o
__STDC__c++11: ${OUTPUT}__STDC__c++11.cpp.o
__STDC__c++14: ${OUTPUT}__STDC__c++14.cpp.o
__STDC__c++17: ${OUTPUT}__STDC__c++17.cpp.o
__STDC__c++20: ${OUTPUT}__STDC__c++20.cpp.o
__STDC__c++23: ${OUTPUT}__STDC__c++23.cpp.o
format: ${OUTPUT}format.cpp.o
fmt: ${OUTPUT}fmt.cpp.o
expired: ${OUTPUT}expired.cpp.o
