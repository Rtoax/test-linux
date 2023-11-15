#!/bin/bash
make hello
gdb --quiet ./hello < until.gdb
