#!/bin/bash
set -e
# Count each syscall
sudo strace -c ls
