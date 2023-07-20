
# Just support x86_64 right now
ifeq ($(shell uname -m),x86_64)
TARGETS := ioctl_values
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = clang

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

ioctl_values: ioctl_values.o

build: ${TARGETS}
	@echo -e "\033[1;32mExamples: \033[m"
	@echo -e "\033[1;33m./ioctl_values 2>/dev/null | awk '{print \"@ioctls[\"\$$3\"] = \"\$$1\";\"}'\033[m"

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.out: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1;31m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	rm -f ${TARGETS} *.o *.d
