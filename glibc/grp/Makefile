SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



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
	${Q}rm -f ${TARGETS} \
		*.o *.d *.out

