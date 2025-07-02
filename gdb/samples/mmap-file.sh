#!/bin/bash
make hello
file=a.bin
dd if=/dev/zero of=${file} bs=1024 count=4
gdb --quiet -ex "set \$file = \"${file}\"" -x mmap-file.gdb hello
rm ${file}
