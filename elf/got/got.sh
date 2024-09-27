#!/bin/bash
make

gdb -q _GLOBAL_OFFSET_TABLE_-32 < got.gdb
