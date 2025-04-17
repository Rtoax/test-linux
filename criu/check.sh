#!/bin/bash
set -e

# FIXME: stuck seconds on 5.15.131?
# FIXME: fedora linux 42 aarch64 failed
timeout 3 sudo criu check
