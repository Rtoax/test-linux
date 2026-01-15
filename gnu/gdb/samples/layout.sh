#!/bin/bash
make hello
gdb --quiet ./hello -x layout.gdb
