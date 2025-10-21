target-y :=
target-y += TIOCGWINSZ
target-y += TIOCSWINSZ
target-y += TCSETS TCGETS
target-y += SIOCETHTOOL
target-y += SIOCGIFCONF
target-y += CDROMEJECT
target-y += ifconfig
target-y += num

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
