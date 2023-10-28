#!/bin/bash

# Turn off transparent_hugepage
grubby --update-kernel=/boot/vmlinuz-`uname -r` --args="transparent_hugepage=never kpti=off"

# Startup hugepage
grubby --update-kernel=/boot/vmlinuz-`uname -r` --args="hugepagesz=1GB hugepages=1"
