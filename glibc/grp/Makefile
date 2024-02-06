
TARGETS :=
TARGETS += fgetgrent
TARGETS += getgrent
TARGETS += getgrgid
TARGETS += getgrnam
TARGETS += getgrouplist
TARGETS += initgroups
TARGETS += setgrent
TARGETS += getgroups
TARGETS += demo-pwd-grp

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

fgetgrent: fgetgrent.o
getgrent: getgrent.o
getgrgid: getgrgid.o
getgrnam: getgrnam.o
getgrouplist: getgrouplist.o
initgroups: initgroups.o
setgrent: setgrent.o
getgroups: getgroups.o
demo-pwd-grp: demo-pwd-grp.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out

