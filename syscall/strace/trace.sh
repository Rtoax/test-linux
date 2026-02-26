#!/bin/bash
set -e

# Trace read(2),close(2) only
sudo strace -e trace=open,read,close ls

# Trace exec*
sudo strace -q -e trace=process ls

# Trace file system relate syscall
sudo strace -q -e trace=file ls

# Trace memory syscall
sudo strace -q -e trace=memory ls

# Trace network syscall
sudo strace -q -e trace=network ls

# Trace signal
sudo strace -q -e trace=signal ls
