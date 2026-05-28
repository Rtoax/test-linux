#!/bin/bash
set -e

# ifconfig's RX,TX packages, ...
# same as /proc/self/net/dev
cat /proc/net/dev
