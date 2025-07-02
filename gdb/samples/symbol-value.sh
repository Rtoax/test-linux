#!/bin/bash
make hello
# NOTE: symbol-value is not gdb command
gdb --quiet ./hello -x symbol-value.gdb
