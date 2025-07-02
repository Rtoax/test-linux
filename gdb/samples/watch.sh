#!/bin/bash
make hello
gdb --quiet ./hello -x watch.gdb
