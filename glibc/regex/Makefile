SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += regcomp
TARGETS += re_search
TARGETS += re_match
TARGETS += email
TARGETS += getprocessruntime-regex
TARGETS += printf-format-arg-split
TARGETS += tr069

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -D__USE_GNU=1

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
regcomp: regcomp.o
re_search: re_search.o
re_match: re_match.o
email: email.o
getprocessruntime-regex: getprocessruntime-regex.o
printf-format-arg-split: printf-format-arg-split.o
tr069: tr069.o

# TODO: I don't know why `implicit declaration of function`
CFLAGS_re_search := -Wno-error=implicit-function-declaration
CFLAGS_re_match := -Wno-error=implicit-function-declaration

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
	${Q}rm -f ${TARGETS} *.o *.d *.log *.out
