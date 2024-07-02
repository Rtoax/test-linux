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

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d
