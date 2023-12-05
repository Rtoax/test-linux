

TARGETS_ld := hello


DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS} ${TARGETS_ld}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	as $(<) -o $(@)

$(TARGETS_ld): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	ld -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_ld} *.o *.d core.*
