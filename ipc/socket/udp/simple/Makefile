SHELL = bash

CC := gcc
CXX := g++

TARGETS :=
TARGETS += server
TARGETS += client

TARGETS_CPP :=
TARGETS_CPP += client_cc

build: $(TARGETS) ${TARGETS_CPP}

server: server.o
client: client.o
client_cc: client_cc.oc

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.oc: %.cc
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_CPP): %:
	@echo -e "  LD(cxx)  \033[1;32m$(@)\033[m"
	@$(CXX) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) ${TARGETS_CPP}\033[m"
	@rm -f ${TARGETS} ${TARGETS_CPP} *.o *.oc

