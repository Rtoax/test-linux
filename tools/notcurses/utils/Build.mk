include notcurses.mk

prog-y += ncneofetch.sh
prog-${HAVE_NCPLAYER} += ncplayer.sh
