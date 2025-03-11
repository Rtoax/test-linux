#!/bin/bash
set -e
sudo strace -e trace=unshare --follow-forks "$@"
