TARGETS :=
TARGETS += fegetenv

CC = gcc

CFLAGS := -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -O0 -g

LDFLAGS := ${CFLAGS}

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fegetenv: fegetenv.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
