#!/bin/bash
set -e

SAVED_STTY=$(stty -g)
restore() {
	stty ${SAVED_STTY}
	stty size
	echo Bye
}
trap restore EXIT INT TERM

stty size
stty rows 32 cols 110
stty size
