#!/bin/bash
make hello
gdb --quiet ./hello < break.gdb
