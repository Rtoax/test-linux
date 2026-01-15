#!/bin/bash
make hello
gdb --quiet ./hello -x until.gdb
