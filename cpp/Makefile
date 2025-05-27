# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
CXX := g++
include ../compiler/compiler.mk

sub-dir := demangle

TARGETS :=
TARGETS += hello
TARGETS += alignas
TARGETS += extern_C
TARGETS += pass-arg
TARGETS += return
TARGETS += this
TARGETS += string
TARGETS += __cplusplus
ifeq (${CC_STD_C++20},1)
  TARGETS += format
endif
TARGETS += fmt
TARGETS += __STDC__ __STDC__c++98 __STDC__gnu++98
TARGETS += expired

CXXFLAGS := -Werror -Wall
CXXFLAGS += -DCPP
ifdef DEBUG
  CXXFLAGS += -DDEBUG -O0 -g -ggdb
endif
ifdef ERROR
  CXXFLAGS += -DERROR=1
endif

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

include ../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o
alignas: alignas.o
extern_C: extern_C.o
pass-arg: pass-arg.o
return: return.o
this: this.o
string: string.o
__cplusplus: __cplusplus.o
__STDC__: __STDC__.o
__STDC__c++98: __STDC__c++98.o
__STDC__gnu++98: __STDC__gnu++98.o
format: format.o
fmt: fmt.o
expired: expired.o


%.o: %.cpp
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -S $(<) -o $(<:.cpp=.s)

${TARGETS}: %:
	@echo -e "  LD   \033[1;32m$(@)\033[m"
	${Q}$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) $(^)

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s

include ../template/subdir-footer.mk
