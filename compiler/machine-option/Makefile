TARGETS :=
TARGETS += mbranch-protection

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes


CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
ifeq ($(shell uname -m),aarch64)
CFLAGS_mbranch-protection += -march=armv8.3-a
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

mbranch-protection: mbranch-protection.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<) || true
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s) || true
	$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error || true

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS) || true

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
