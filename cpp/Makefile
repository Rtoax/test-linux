include ../tlbuild.mk

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

CXX = g++

CXXFLAGS := -Werror -Wall
CXXFLAGS += -DCPP
ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif

ifdef M32
  CFLAGS += -m32 -DM32=1
  CXXFLAGS += -m32 -DM32=1
  $(info Compile 32bit ELF)
endif

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

CXXFLAGS_return := -Wno-error=return-type

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
