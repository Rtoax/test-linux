#!/bin/bash
make hello
gdb --quiet ./hello -x define.gdb
