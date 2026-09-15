#!/bin/bash
set -e

my_uname()
{
	echo "rtoax"
}

uname

shopt -s expand_aliases
alias uname=my_uname
uname
