SHELL = bash
LLVM_CONFIG = $(shell which llvm-config 2>/dev/null)
CXX = clang++

ifeq ($(CXX),)
  $(warning Not found ${CXX}, please install first)
endif

TARGETS :=
TARGETS += ParseCommandLineOptions
TARGETS += ParseCommandLineOptions-2

CXXFLAGS :=
CXXFLAGS += -Werror -Wall
CXXFLAGS += -Wstrict-prototypes
CXXFLAGS += -DDEBUG -O0 -g

ifeq ($(LLVM_CONFIG),)
  $(warning Not found llvm-config, please install llvm first)
else
  CXXFLAGS += $(shell llvm-config --cxxflags --ldflags --system-libs --libs core mc mcjit ExecutionEngine)
endif


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
ParseCommandLineOptions: ParseCommandLineOptions.o
ParseCommandLineOptions-2: ParseCommandLineOptions-2.o

CXXFLAGS_ParseCommandLineOptions := -Wno-unused-command-line-argument
CXXFLAGS_ParseCommandLineOptions-2 := -Wno-unused-command-line-argument

%.o: %.cpp
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CXX) $(CXXFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
