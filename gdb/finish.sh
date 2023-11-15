#!/bin/bash
make hello
gdb --quiet ./hello < finish.gdb
