#!/bin/bash
set -e

gotoxy()
{
	printf "\033[%d;%df" ${1} ${2}
}

gotoxy 10 10
