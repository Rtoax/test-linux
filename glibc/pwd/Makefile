TARGETS :=
TARGETS += setpwent getpwent endpwent
TARGETS += putpwent
TARGETS += getpwnam
TARGETS += getpwuid
TARGETS += demo-pwd-grp

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

setpwent: setpwent.o
getpwent: getpwent.o
endpwent: endpwent.o
putpwent: putpwent.o
getpwnam: getpwnam.o
getpwuid: getpwuid.o
demo-pwd-grp: demo-pwd-grp.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o new_passwd

