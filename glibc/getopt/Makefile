TARGETS :=
TARGETS += getopt
TARGETS += getopt_long
TARGETS += getsubopt
TARGETS += demo-wls
TARGETS += demo-clr

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
getopt: getopt.o
getopt_long: getopt_long.o
getsubopt: getsubopt.o
demo-wls: demo-wls.o
demo-clr: demo-clr.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
