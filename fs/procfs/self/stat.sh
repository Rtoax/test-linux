#!/bin/bash
set -e

STAT="/proc/$$/stat"

tty_nr=$(awk '{print $7}' ${STAT})

tty_major=$( printf "%d" $(( (${tty_nr} >> 8) & 0xFF )) )
tty_minor=$( printf "%d" $(( ${tty_nr} & 0xFF )) )
echo "TTY $tty_major:$tty_minor"
