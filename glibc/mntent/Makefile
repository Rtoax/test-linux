TARGETS :=
TARGETS += getmntent getmntent_r
TARGETS += setmntent

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

getmntent: getmntent.o
getmntent_r: getmntent_r.o
setmntent: setmntent.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

