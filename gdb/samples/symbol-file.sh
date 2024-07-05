#!/bin/bash
make hello.strip
gdb --quiet hello.strip < symbol-file.gdb
