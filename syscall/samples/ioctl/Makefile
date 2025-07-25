targets :=
targets += TIOCGWINSZ
targets += TIOCSWINSZ
targets += TCSETS TCGETS
targets += SIOCETHTOOL
targets += SIOCGIFCONF
targets += CDROMEJECT
targets += ifconfig
targets += num

include ../../../template/main.mk

SIOCETHTOOL: SIOCETHTOOL.o
TIOCGWINSZ: TIOCGWINSZ.o
TIOCSWINSZ: TIOCSWINSZ.o
TCSETS: TCSETS.o
TCGETS: TCGETS.o
SIOCGIFCONF: SIOCGIFCONF.o
CDROMEJECT: CDROMEJECT.o
ifconfig: ifconfig.o
num: num.o
