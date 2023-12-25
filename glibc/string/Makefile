TARGETS += bcopy
TARGETS += index
TARGETS += memchr
TARGETS += memcpy
TARGETS += memset
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
TARGETS += strsignal

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -O0 -g -ggdb

ifdef SIMD
CFLAGS += -mavx2
endif

build: sig.h ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

sig.h:
	$(shell sh signo.sh)

bcopy: bcopy.o
index: index.o
memchr: memchr.o
memcpy: memcpy.o
memset: memset.o
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
strsignal: strsignal.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.log
