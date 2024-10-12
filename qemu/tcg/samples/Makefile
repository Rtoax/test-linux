SHELL = bash

TARGETS := hello

CFLAGS := -static
LDFLAGS := -static

all: ${TARGETS}

hello: hello.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  RM  \033[1;32m$(TARGETS)\033[m"
	@rm -rf ${TARGETS} *.o

