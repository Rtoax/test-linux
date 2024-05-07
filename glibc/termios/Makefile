TARGETS :=
TARGETS += cfsetspeed cfsetospeed cfsetispeed cfgetispeed cfgetospeed
TARGETS += NCCS
TARGETS += tcsetattr tcgetattr
TARGETS += tcgetsid
TARGETS += password

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
cfsetspeed: cfsetspeed.o
cfsetospeed: cfsetospeed.o
cfsetispeed: cfsetispeed.o
cfgetispeed: cfgetispeed.o
cfgetospeed: cfgetospeed.o
NCCS: NCCS.o
tcsetattr: tcsetattr.o
tcgetsid: tcgetsid.o
tcgetattr: tcgetattr.o
password: password.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	echo abcde | ./tcsetattr

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-*
