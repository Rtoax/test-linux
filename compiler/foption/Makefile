
TARGETS :=
TARGETS += fcf-protection
TARGETS += ffat-lto-objects
TARGETS += fpatchable-function-entry
TARGETS += flto
TARGETS += fstack-protector fstack-protector-all fstack-protector-strong fstack-protector-explicit

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

# N,M M=0 by default
CFLAGS_fcf-protection := -fcf-protection
CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
CFLAGS_fpatchable-function-entry := -fpatchable-function-entry=5,2
CFLAGS_flto := -flto=auto
CFLAGS_fstack-protector := -fstack-protector
CFLAGS_fstack-protector-all := -fstack-protector-all
CFLAGS_fstack-protector-strong := -fstack-protector-strong
CFLAGS_fstack-protector-explicit := -fstack-protector-explicit

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

fcf-protection: fcf-protection.o
ffat-lto-objects: ffat-lto-objects.o
fpatchable-function-entry: fpatchable-function-entry.o
flto: flto.o
fstack-protector: fstack-protector.o
fstack-protector-all: fstack-protector-all.o
fstack-protector-explicit: fstack-protector-explicit.o
fstack-protector-strong: fstack-protector-strong.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
