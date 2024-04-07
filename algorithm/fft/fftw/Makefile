TARGETS :=
TARGETS += fftw_plan_dft_1d

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lm

ifneq ($(wildcard /usr/include/fftw3.h),)
CFLAGS += -lfftw3
else
$(error "Not found fftw header")
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fftw_plan_dft_1d: fftw_plan_dft_1d.o

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
	@rm -f ${TARGETS} *.o *.d
