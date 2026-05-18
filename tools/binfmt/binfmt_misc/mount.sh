#!/bin/bash
set -e

# or add to /etc/fstab:
#  none  /proc/sys/fs/binfmt_misc binfmt_misc defaults 0 0
sudo mount -t binfmt_misc none /proc/sys/fs/binfmt_misc
