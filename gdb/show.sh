#!/bin/bash
make hello
gdb --quiet ./hello < show.gdb
