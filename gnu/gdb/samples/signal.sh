#!/bin/bash
make hello
gdb --quiet ./hello -x signal.gdb
