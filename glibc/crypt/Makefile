TARGETS := crypt
TARGETS += encrypt

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lcrypt
CFLAGS += -D_XOPEN_SOURCE -D_GNU_SOURCE
CFLAGS += -Wno-error=implicit-function-declaration

LDFLAGS := -lcrypt

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
crypt: crypt.o
encrypt: encrypt.o

CFLAGS_crypt := -lcrypt

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
