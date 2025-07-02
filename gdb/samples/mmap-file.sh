#!/bin/bash
make hello
file=a.bin
gdb --quiet -ex "set \$file = \"${file}\"" -x mmap-file.gdb hello
