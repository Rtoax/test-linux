# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
CXX := g++
include ../compiler/compiler.mk

sub-dir := demangle

TARGETS_CPP :=
TARGETS_CPP += hello
TARGETS_CPP += alignas
TARGETS_CPP += extern_C
TARGETS_CPP += pass-arg
TARGETS_CPP += return
TARGETS_CPP += this
TARGETS_CPP += string
TARGETS_CPP += __cplusplus
ifeq (${CC_STD_C++20},1)
  TARGETS_CPP += format
endif
TARGETS_CPP += fmt
TARGETS_CPP += __STDC__ __STDC__c++98 __STDC__gnu++98
TARGETS_CPP += expired

CXXFLAGS := -Werror -Wall
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
CXXFLAGS_fmt := -lfmt

TARGETS_EXTRA := $(patsubst %,%.cpp.s,${TARGETS_CPP})

#	${Q}$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -S $(<) -o $(<:.cpp=.s)
include ../template/main.mk

hello: hello.opp
alignas: alignas.opp
extern_C: extern_C.opp
pass-arg: pass-arg.opp
return: return.opp
this: this.opp
string: string.opp
__cplusplus: __cplusplus.opp
__STDC__: __STDC__.opp
__STDC__c++98: __STDC__c++98.opp
__STDC__gnu++98: __STDC__gnu++98.opp
format: format.opp
fmt: fmt.opp
expired: expired.opp
