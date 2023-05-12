#!/bin/bash

gcc hello.c -g -o hello

cat <<-EOF
.debug_info: dwarfdump --print-info (-i)
.debug_abbrev: dwarfdump --print-abbrev (-b)
.debug_frame: dwarfdump --print-frame (-f)
.debug_line: dwarfdump --print-lines (-l)
.debug_str: dwarfdump --print-strings (-s)
EOF
