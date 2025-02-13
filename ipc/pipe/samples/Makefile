include ../../../tlbuild.mk


TARGETS := pipe-size
TARGETS += pipe
TARGETS += pipe-fork
TARGETS += pipe-broken-pipe shutdown-broken-pipe

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lpthread

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
pipe-size: pipe-size.o
pipe: pipe.o
pipe-fork: pipe-fork.o
pipe-broken-pipe: pipe-broken-pipe.o
shutdown-broken-pipe: shutdown-broken-pipe.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
