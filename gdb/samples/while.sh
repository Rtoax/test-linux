#!/bin/bash
make hello
gdb --quiet ./hello < while.gdb
