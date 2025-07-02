#!/bin/bash
make hello
gdb --quiet ./hello -x disassemble.gdb
