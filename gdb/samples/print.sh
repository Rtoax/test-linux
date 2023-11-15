#!/bin/bash
make hello
gdb --quiet ./hello < print.gdb
