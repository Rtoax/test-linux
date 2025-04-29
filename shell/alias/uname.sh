#!/bin/bash
set -e

export MY_ARCH=$(uname -m)

my_uname()
{
	case $1 in
	-m)
		echo $MY_ARCH
		;;
	*)
		echo "No arg"
		;;
	esac
}

uname -m

source ./config.sh
echo $MY_ARCH
uname -m

unset MY_ARCH
export MY_ARCH=myarch
shopt -s expand_aliases
alias uname=my_uname
uname -m

source ./config.sh
echo $MY_ARCH
