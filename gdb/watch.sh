#!/bin/bash
make hello
gdb --quiet ./hello < watch.gdb
