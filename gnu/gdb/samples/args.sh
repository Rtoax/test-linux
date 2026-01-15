#!/bin/bash
make hello
gdb --quiet -x args.gdb ./hello
