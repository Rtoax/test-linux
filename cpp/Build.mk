# SPDX-License-Identifier: GPL-3.0
include compiler.mk

SRC_SFX_LIST := $(shell seq 1 1 20)

subdir-y := demangle
subdir-y += std

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
target-cpp-y += __STDC__c++03 __STDC__gnu++03
target-cpp-y += __STDC__c++11 __STDC__gnu++11
target-cpp-y += __STDC__c++14 __STDC__gnu++14
target-cpp-y += __STDC__c++17 __STDC__gnu++17
target-cpp-${CC_STD_C++20} += __STDC__c++20 __STDC__gnu++20
target-cpp-${CC_STD_C++23} += __STDC__c++23 __STDC__gnu++23
target-cpp-${CC_STD_C++26} += __STDC__c++26 __STDC__gnu++26
target-cpp-y += expired
target-cpp-y += unordered_map

__STDC__c++98-objs := __STDC__.1.cpp.o
__STDC__c++03-objs := __STDC__.2.cpp.o
__STDC__c++11-objs := __STDC__.3.cpp.o
__STDC__c++14-objs := __STDC__.4.cpp.o
__STDC__c++17-objs := __STDC__.5.cpp.o
__STDC__c++20-objs := __STDC__.6.cpp.o
__STDC__c++23-objs := __STDC__.7.cpp.o
__STDC__c++26-objs := __STDC__.8.cpp.o

__STDC__gnu++98-objs := __STDC__.10.cpp.o
__STDC__gnu++03-objs := __STDC__.11.cpp.o
__STDC__gnu++11-objs := __STDC__.12.cpp.o
__STDC__gnu++14-objs := __STDC__.13.cpp.o
__STDC__gnu++17-objs := __STDC__.14.cpp.o
__STDC__gnu++20-objs := __STDC__.15.cpp.o
__STDC__gnu++23-objs := __STDC__.16.cpp.o
__STDC__gnu++26-objs := __STDC__.17.cpp.o

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

CXXFLAGS___STDC__.1 := -std=c++98
CXXFLAGS___STDC__.2 := -std=c++03
CXXFLAGS___STDC__.3 := -std=c++11
CXXFLAGS___STDC__.4 := -std=c++14
CXXFLAGS___STDC__.5 := -std=c++17
CXXFLAGS___STDC__.6 := -std=c++20
CXXFLAGS___STDC__.7 := -std=c++23
CXXFLAGS___STDC__.8 := -std=c++26

CXXFLAGS___STDC__.10 := -std=gnu++98
CXXFLAGS___STDC__.11 := -std=gnu++03
CXXFLAGS___STDC__.12 := -std=gnu++11
CXXFLAGS___STDC__.13 := -std=gnu++14
CXXFLAGS___STDC__.14 := -std=gnu++17
CXXFLAGS___STDC__.15 := -std=gnu++20
CXXFLAGS___STDC__.16 := -std=gnu++23
CXXFLAGS___STDC__.17 := -std=gnu++26

CXXFLAGS_string := -std=c++23
LDXXFLAGS_fmt := -lfmt
