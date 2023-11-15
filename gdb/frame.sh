#!/bin/bash
make hello
gdb --quiet ./hello < frame.gdb
