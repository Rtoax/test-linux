#!/bin/bash
make hello
gdb --quiet ./hello < disassemble.gdb
