#!/bin/bash
set -e

# enter this pid namespace with:
# $ sudo nsenter --pid --mount --target ${pid-of-bash}
sudo unshare --pid --fork --mount-proc bash
