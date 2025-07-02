#!/bin/bash
make hello
gdb --quiet ./hello -x list.gdb
