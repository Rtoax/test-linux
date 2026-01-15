#!/bin/bash
make hello
gdb --quiet ./hello -x directory.gdb
