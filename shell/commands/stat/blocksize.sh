#!/bin/bash
# see fedora-coreos-config

set -euo pipefail

mem=$(stat -f -c "%b * %s / 1024" /)
echo $mem
