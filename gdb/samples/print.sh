#!/bin/bash
make hello
gdb --quiet ./hello -x print.gdb
