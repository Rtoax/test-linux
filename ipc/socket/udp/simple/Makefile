SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


CC := gcc
CXX := g++

TARGETS :=
TARGETS += server client
TARGETS += stress-send stress-recv

TARGETS_CPP :=
TARGETS_CPP += client_cc

build: $(TARGETS) ${TARGETS_CPP}

server: server.o
client: client.o
client_cc: client_cc.oc
stress-send: stress-send.o
stress-recv: stress-recv.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.oc: %.cc
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_CPP): %:
	@echo -e "  LD(cxx)  \033[1;32m$(@)\033[m"
	${Q}$(CXX) -o $(@) $(^) $(CXXFLAGS) $(CXXFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) ${TARGETS_CPP}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_CPP} *.o *.oc

