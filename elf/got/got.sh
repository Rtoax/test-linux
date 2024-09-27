#!/bin/bash
make
gdb -q _GLOBAL_OFFSET_TABLE_ < got.gdb
