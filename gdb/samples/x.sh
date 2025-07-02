#!/bin/bash
make hello
gdb --quiet ./hello -x x.gdb
