#!/bin/bash

set -e

tmpfs=/path/to/mountpoint

sudo fsfreeze --freeze ${tmpfs}
cat /etc/os-release > ${tmpfs}/os-release
sudo fsfreeze --unfreeze ${tmpfs}

