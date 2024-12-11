SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


FFTW_HDR = /usr/include/fftw3.h

TARGETS :=
ifneq ($(wildcard ${FFTW_HDR}),)
TARGETS += fftw_plan_dft_1d
TARGETS += fftw_plan_dft_1d-1
TARGETS += fftw_plan_dft_r2c_1d
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lm

ifneq ($(wildcard ${FFTW_HDR}),)
CFLAGS += -lfftw3
else
$(warning "Not found header ${FFTW_HDR}, please install fftw")
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fftw_plan_dft_1d: fftw_plan_dft_1d.o
fftw_plan_dft_1d-1: fftw_plan_dft_1d-1.o
fftw_plan_dft_r2c_1d: fftw_plan_dft_r2c_1d.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
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
