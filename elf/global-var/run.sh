#!/bin/bash

gcc -O0 bss.c -o bss
readelf --syms bss | grep ___
readelf -S bss | grep -e bss -e data -e rodata

