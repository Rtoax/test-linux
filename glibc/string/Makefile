TARGETS += bcopy
TARGETS += index
TARGETS += memchr
TARGETS += memcpy
TARGETS += memmove
TARGETS += stpcpy
TARGETS += strcmp
TARGETS += strcat
TARGETS += strchr
TARGETS += strcpy
TARGETS += strdupa
TARGETS += strdup
TARGETS += strlen
TARGETS += strncpy
TARGETS += strpbrk
TARGETS += strsep
TARGETS += strtok
TARGETS += strtol

ifeq ($(shell uname -m),x86_64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
bcopy: bcopy.o
index: index.o
memchr: memchr.o
memcpy: memcpy.o
memmove: memmove.o
stpcpy: stpcpy.o
strcat: strcat.o
strchr: strchr.o
strcpy: strcpy.o
strcmp: strcmp.o
strdupa: strdupa.o
strdup: strdup.o
strlen: strlen.o
strncpy: strncpy.o
strpbrk: strpbrk.o
strsep: strsep.o
strtok: strtok.o
strtol: strtol.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
