SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += set-value
TARGETS += set-value-func
TARGETS += set-value-volatile
TARGETS += pthread-gdb
TARGETS += hello
TARGETS += linklist
TARGETS += daxpy

TARGETS_STRIP := hello.strip

TARGETS_CPP := global-var

# Get all .sh suffix scripts
SCRIPTS := $(shell ls *.sh)
# Output .sh.log suffix file list
SCRIPTS_OUT = $(foreach s,${SCRIPTS},${s}.log)

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall
CFLAGS += -O0 -ggdb
CFLAGS += -pthread

CXXFLAGS :=
CXXFLAGS += -O0 -ggdb

ifneq ($(PIE),)
  CFLAGS += -fpie
  LDFLAGS += -pie
  CXXFLAGS += -fpie
endif

CFLAGS_hello := -Wno-error=unused-function

build: ${TARGETS} ${TARGETS_STRIP} ${TARGETS_CPP} ${SCRIPTS_OUT}
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

# Strip
hello.strip: hello

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

# The following two commands same as
#  @eu-strip hello -f hello.debug -o hello.strip
define mystrip
	@objcopy --only-keep-debug $(1) $(1).debug
	@strip $(1) -o $(1).strip
endef

$(TARGETS_STRIP): %:
	@echo -e "  STRIP  \033[1;32m$(@)\033[m"
	$(call mystrip,$(^))

%.opp: %.cpp
	$(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

$(TARGETS_CPP): %:
	$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*)) $(CXXFLAGS) $(CXXFLAGS_$(*))

.PHONY: test
test: ${SCRIPTS_OUT}
	@echo "Test Done"

${SCRIPTS_OUT}: %:
	@echo "Testing \033[1;32m$(basename $(@))\033[m"
	# Strip suffix and execute
	./$(basename $(@)) | tee $(@)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_STRIP) ${TARGETS_CPP} ${SCRIPTS_OUT}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_STRIP} ${TARGETS_CPP} ${SCRIPTS_OUT}
	${Q}rm -f *.o *.opp *.log *.debug *.strip
