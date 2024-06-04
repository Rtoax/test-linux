sub-dir := readline

TARGETS :=
TARGETS += byteswap
TARGETS += endian
TARGETS += gotoxy goprint
TARGETS += log
TARGETS += memshow
TARGETS += mac
TARGETS += proc_examples
TARGETS += progress
TARGETS += str
TARGETS += ipaddr

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS_proc_examples += -DTEST=1
CFLAGS_progress += -DTEST=1
CFLAGS_mac := -DTEST=1
CFLAGS_str := -DTEST=1

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
byteswap: byteswap.o
endian: endian.o
gotoxy: gotoxy.o
goprint: goprint.o
log: log.o
memshow: memshow.o
mac: mac.o
progress: progress.o
proc_examples: proc_examples.o proc.o
str: str.o
ipaddr: ipaddr.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean

