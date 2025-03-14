include ../../../tlbuild.mk


CC := gcc
CFLAGS := -O0 -g -ggdb

TARGETS :=

ifeq ($(shell uname -m),x86_64)
TARGETS += rdpkru
endif

all: $(TARGETS)

rdpkru: rdpkru.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o
