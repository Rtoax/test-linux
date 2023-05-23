#!/bin/bash

log()
{
	echo -e "\033[32m $@ \033[m"
}

log "No -ftree-vectorize"
gcc -O2 -S -c sum.c -o /dev/stdout

log "Use -ftree-vectorize"
gcc -O2 -ftree-vectorize -S -c sum.c -o /dev/stdout

