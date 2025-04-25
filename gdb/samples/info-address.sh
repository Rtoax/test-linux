#!/bin/bash
make hello
gdb --quiet ./hello < info-address.gdb
