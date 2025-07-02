#!/bin/bash
make hello
gdb --quiet ./hello -x dump-memory.gdb
