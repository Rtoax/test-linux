
TARGETS += hello
TARGETS += alignas

DEBUG = yes
SRC_PATH := $(shell pwd)
CXX = g++

CXXFLAGS := -Werror -Wall
CXXFLAGS += -I../macro/

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g -ggdb
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o
alignas: alignas.o

%.o: %.cpp
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) -c $(<)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -S $(<) -o $(<:.cpp=.s)

${TARGETS}: %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CXX) $(CXXFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)


test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
