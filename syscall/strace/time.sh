#!/bin/bash
set -e

# Show called time
sudo strace -t ls

# Show spent time
sudo strace -T ls
