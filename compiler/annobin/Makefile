TARGETS :=
TARGETS += hello

CC = gcc
ANNOBIN = $(shell pwd)/annobin-cc1

ifneq ($(wildcard /usr/lib/rpm/redhat/redhat-annobin-cc1),)
$(info Found /usr/lib/rpm/redhat/redhat-annobin-cc1)
ANNOBIN = /usr/lib/rpm/redhat/redhat-annobin-cc1
endif

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -specs=$(ANNOBIN)

LDFLAGS :=
LDLIBS :=

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
