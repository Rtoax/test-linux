#!/bin/bash
set -e

# execute:
# - bash -c "sleep infinity & exec bash"
# - bash -c "tail -f /dev/null & exec bash"
# - ./dummy_init
sudo unshare --pid --fork --mount-proc bash

# enter this pid namespace with:
# $ sudo nsenter --pid --mount --target ${pid-of-bash}
