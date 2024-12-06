SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += fegetenv
TARGETS += feclearexcept
TARGETS += fegetround
TARGETS += feraiseexcept
TARGETS += fesetround
TARGETS += fetestexcept
TARGETS += demo-exception

CC = gcc

CFLAGS := -Wall
CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -O0 -g

LDFLAGS := ${CFLAGS}

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fegetenv: fegetenv.o
feclearexcept: feclearexcept.o
fegetround: fegetround.o
feraiseexcept: feraiseexcept.o
fesetround: fesetround.o
fetestexcept: fetestexcept.o
demo-exception: demo-exception.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
