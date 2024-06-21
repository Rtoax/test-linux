TARGETS :=
TARGETS += bignum

CC = gcc

LDFLAGS :=
LDLIBS :=

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/
CFLAGS += -DDEBUG -O0 -g -ggdb
CFLAGS +=$(shell pkg-config --libs --cflags openssl)

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
bignum: bignum.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.cer *.pem
