SHELL = bash
include ../../../tlbuild.mk


TARGETS :=
TARGETS += hello

CFLAGS := -Werror -Wall
CFLAGS_DBG := -g

ifdef DWARF5
  CFLAGS += -gdwarf-5
endif
ifdef DWARF4
  CFLAGS += -gdwarf-4
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

CFLAGS_hello += -Wno-error=unused-variable

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_DBG) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_DBG) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	${Q}$(CC) $(CFLAGS)               $(CFLAGS_$(*)) -S $(<) -o $(<:.c=-nodebuginfo.s)
	@echo "--------- show different --------"
	@diff -up $(<:.c=-nodebuginfo.s) $(<:.c=.s) | nl | sed "s|^|$(*): |g" || true

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)
	dwz $(@) -o $(@).dwz
	eu-strip $(@) -f $(@).debug -o $(@).strip

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s *.dwz *.debug *.strip
