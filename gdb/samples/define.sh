#!/bin/bash
make hello
gdb --quiet ./hello < define.gdb
