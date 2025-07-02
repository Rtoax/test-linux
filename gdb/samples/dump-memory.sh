#!/bin/bash
make hello
gdb --quiet ./hello < dump-memory.gdb
