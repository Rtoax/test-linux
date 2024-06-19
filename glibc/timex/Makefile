TARGETS :=
TARGETS += ntp_adjtime
TARGETS += ntp_gettime

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
ntp_adjtime: ntp_adjtime.o
ntp_gettime: ntp_gettime.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
