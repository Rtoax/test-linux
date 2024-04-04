TARGETS :=
TARGETS += opendir
TARGETS += readdir
TARGETS += telldir
TARGETS += seekdir
TARGETS += listdir
TARGETS += fdopendir

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
opendir: opendir.o
readdir: readdir.o
telldir: telldir.o
seekdir: seekdir.o
listdir: listdir.o
fdopendir: fdopendir.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
