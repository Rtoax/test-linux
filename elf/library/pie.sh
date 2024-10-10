#!/bin/bash
set -e
make clean
make PIE=1 "$@"
