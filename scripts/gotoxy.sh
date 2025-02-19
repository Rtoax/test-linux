#!/bin/bash
set -e

gotoxy()
{
	printf "\033[%d;%df" ${1} ${2}
}

if [[ $(basename $0) == gotoxy.sh ]]; then
	gotoxy 10 10
fi
