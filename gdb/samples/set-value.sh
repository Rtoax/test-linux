#!/bin/bash

make clean && make

gdb -q set-value < set-value.gdb
gdb -q set-value-func < set-value.gdb
gdb -q set-value-volatile < set-value.gdb
