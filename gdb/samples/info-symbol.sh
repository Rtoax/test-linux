#!/bin/bash
make hello
gdb --quiet ./hello < info-symbol.gdb
