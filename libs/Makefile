
TARGETS := gotoxy goprint
TARGETS += log
TARGETS += memshow
TARGETS += progress

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS_progress += -DTEST=1

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
gotoxy: gotoxy.o
goprint: goprint.o
log: log.o
memshow: memshow.o
progress: progress.o


%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
