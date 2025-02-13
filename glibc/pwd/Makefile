SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += setpwent getpwent endpwent
TARGETS += putpwent
TARGETS += getpwnam
TARGETS += getpwuid
TARGETS += fgetpwent
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
fgetpwent: fgetpwent.o
demo-pwd-grp: demo-pwd-grp.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o new_passwd

