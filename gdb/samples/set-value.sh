#!/bin/bash

make set-value set-value-func set-value-volatile

gdb -q set-value -x set-value.gdb
gdb -q set-value-func -x set-value.gdb
gdb -q set-value-volatile -x set-value.gdb
