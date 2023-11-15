#!/bin/bash
make hello
gdb --quiet ./hello < args.gdb
