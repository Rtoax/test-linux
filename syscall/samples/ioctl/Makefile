TARGETS :=
TARGETS += TIOCGWINSZ
TARGETS += TIOCSWINSZ
TARGETS += SIOCETHTOOL
TARGETS += SIOCGIFCONF
TARGETS += CDROMEJECT
TARGETS += ifconfig
TARGETS += num

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
SIOCETHTOOL: SIOCETHTOOL.o
TIOCGWINSZ: TIOCGWINSZ.o
TIOCSWINSZ: TIOCSWINSZ.o
SIOCGIFCONF: SIOCGIFCONF.o
CDROMEJECT: CDROMEJECT.o
ifconfig: ifconfig.o
num: num.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./main.user.out

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
