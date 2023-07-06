#!/bin/bash

gcc -O0 bss.c -o bss
readelf --sym bss | grep ___
readelf -S bss | grep -e bss -e data


