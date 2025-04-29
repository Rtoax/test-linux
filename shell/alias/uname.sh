#!/bin/bash
set -e

export OSTOOLS_ARCH=$(uname -m)

my_uname()
{
	case $1 in
	-m)
		echo $OSTOOLS_ARCH
		;;
	*)
		echo "No arg"
		;;
	esac
}

uname -m

source ./config.sh
echo $OSTOOLS_ARCH
uname -m

unset OSTOOLS_ARCH
export OSTOOLS_ARCH=myarch
shopt -s expand_aliases
alias uname=my_uname
uname -m

source ./config.sh
echo $OSTOOLS_ARCH
