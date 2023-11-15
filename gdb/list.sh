#!/bin/bash
make hello
gdb --quiet ./hello < list.gdb
