#!/bin/bash
make hello
gdb --quiet ./hello -x frame.gdb
