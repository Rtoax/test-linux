#!/bin/bash

make clean && make

gdb -q set-value < set-value.gdb
gdb -q set-value-ok < set-value.gdb
