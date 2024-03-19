
TARGETS :=
TARGETS += getrlimit setrlimit ulimit prlimit
TARGETS += fork-inherit
TARGETS += getrusage

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
getrlimit: getrlimit.o helpers.o
setrlimit: setrlimit.o helpers.o
prlimit: prlimit.o helpers.o
ulimit: ulimit.o
fork-inherit: fork-inherit.o helpers.o
getrusage: getrusage.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -rf ${TARGETS} *.o

