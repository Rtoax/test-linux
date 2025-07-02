#!/bin/bash
make hello.strip
# Skip: Enable debuginfod for this session? (y or [n])
DEBUGINFOD_URLS="" gdb --quiet hello.strip -x symbol-file.gdb
