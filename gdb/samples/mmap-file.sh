#!/bin/bash
make hello
gdb --quiet ./hello -x mmap-file.gdb
