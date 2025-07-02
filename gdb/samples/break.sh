#!/bin/bash
make hello
gdb --quiet ./hello -x break.gdb
