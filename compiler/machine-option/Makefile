
TARGETS :=
TARGETS += mbranch-protection

ifneq ($(shell uname -m),aarch64)
TARGETS += fcf-protection
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

CFLAGS_mbranch-protection := -mbranch-protection=pac-ret

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

mbranch-protection: mbranch-protection.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
