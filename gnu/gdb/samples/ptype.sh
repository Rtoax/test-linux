#!/bin/bash
make hello
gdb --quiet ./hello -x ptype.gdb
