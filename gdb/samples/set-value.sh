#!/bin/bash

make set-value set-value-func set-value-volatile

gdb -q set-value < set-value.gdb
gdb -q set-value-func < set-value.gdb
gdb -q set-value-volatile < set-value.gdb
