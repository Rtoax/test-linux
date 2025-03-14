include ../../../tlbuild.mk



TARGETS := rbtree_test

# Add more object.o file
rbtree_test: rbtree_test.o rbtree.o

DEBUG := yes
CC := gcc

CFLAGS :=

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^)

test: ${TARGETS}
	./rbtree_test >/dev/null

clean:
	${Q}rm -f ${TARGETS} *.o *.d
