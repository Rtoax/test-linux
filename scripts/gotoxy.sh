#!/bin/bash
set -e

gotoxy() {
	local x=$2 y=$1
	printf "\033[%d;%df" ${y} ${x}
}

if [[ $(basename $0) == gotoxy.sh ]]; then
	gotoxy 10 10
fi
