
TARGETS_ld := hello

DEBUG = yes
CC = gcc
AS = as
LD = ld
RUN_PFX =

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

ifneq ($(shell uname -m),aarch64)
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	RUN_PFX = qemu-aarch64
endif

.PHONY: build
build: ${TARGETS} ${TARGETS_ld}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(AS) $(<) -o $(@)

$(TARGETS_ld): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_ld} *.o *.d core.*
