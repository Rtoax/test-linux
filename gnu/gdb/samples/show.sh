#!/bin/bash
make hello
gdb --quiet ./hello -x show.gdb
