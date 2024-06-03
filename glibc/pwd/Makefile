TARGETS :=
TARGETS += setpwent getpwent endpwent
TARGETS += demo-pwd-grp

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

setpwent: setpwent.o
getpwent: getpwent.o
endpwent: endpwent.o
demo-pwd-grp: demo-pwd-grp.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

