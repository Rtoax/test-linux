
TARGETS += clone
TARGETS += ns_pid
TARGETS += ns_net
TARGETS += container
TARGETS += uts_hostname

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

clone: clone.o
ns_pid: ns_pid.o
ns_net: ns_net.o
container: container.o
uts_hostname: uts_hostname.o

CFLAGS_ns_pid := -Wno-error=int-to-pointer-cast

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d

