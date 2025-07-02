#!/bin/bash
make hello
gdb --quiet ./hello -x info.gdb
