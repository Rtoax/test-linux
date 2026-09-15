#!/bin/bash

read -r -N 8 bin < "$1"

case $bin in
$'\x71\xc7'* | 070701)
    TYPE="ASCII cpio archive"
    ;;
$'\x7f'ELF*)
    TYPE="ELF"
    ;;
PERFILE2*)
    TYPE="perf.data"
    ;;
esac

echo "Type $TYPE"

