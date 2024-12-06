SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += ceil
TARGETS += copysign
TARGETS += exp
TARGETS += fpclassify
TARGETS += finite
TARGETS += sqrt sqrt-stress
TARGETS += nan
TARGETS += isgreater
TARGETS += log log-stress
TARGETS += sin
TARGETS += signbit
TARGETS += nextafter

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

LDFLAGS := ${CFLAGS}

CFLAGS_sqrt-stress := -DSTRESS=1
CFLAGS_log-stress := -DSTRESS=1

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
ceil: ceil.o
exp: exp.o
sqrt: sqrt.o
sqrt-stress: sqrt-stress.o
copysign: copysign.o
fpclassify: fpclassify.o
finite: finite.o
nan: nan.o
isgreater: isgreater.o
log: log.o
log-stress: log-stress.o
sin: sin.o
signbit: signbit.o
nextafter: nextafter.o

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
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-*
