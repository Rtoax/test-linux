
TARGETS := fpatchable-function-entry

CC = gcc

CFLAGS := -Werror -Wall

# N,M M=0 by default
CFLAGS_fpatchable-function-entry := -fpatchable-function-entry=5,2

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

fpatchable-function-entry: fpatchable-function-entry.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
