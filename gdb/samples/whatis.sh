#!/bin/bash
make hello
gdb --quiet ./hello < whatis.gdb
