#!/bin/bash
make hello
gdb --quiet ./hello -x whatis.gdb
