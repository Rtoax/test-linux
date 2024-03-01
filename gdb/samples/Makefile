
TARGETS := set-value
TARGETS += set-value-func
TARGETS += set-value-volatile
TARGETS += pthread-gdb
TARGETS += hello
TARGETS += linklist
TARGETS += daxpy

TARGETS_CPP := global-var

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall
CFLAGS += -O0 -ggdb

CXXFLAGS :=
CXXFLAGS += -O0 -ggdb

ifneq ($(PIE),)
CFLAGS += -fpie
LDFLAGS += -pie
CXXFLAGS += -fpie
endif

build: ${TARGETS} ${TARGETS_CPP}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
set-value: set-value.o
set-value-func: set-value-func.o
set-value-volatile: set-value-volatile.o
pthread-gdb: pthread-gdb.o
hello: hello.o
linklist: linklist.o
daxpy: daxpy.o
global-var: global-var.opp


%.opp: %.cpp
	$(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

$(TARGETS_CPP): %:
	$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*)) $(CXXFLAGS) $(CXXFLAGS_$(*))

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_CPP} *.o *.d *.opp
