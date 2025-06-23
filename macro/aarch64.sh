#!/bin/bash
set -e
make clean
make STATIC=1 CROSS_COMPILE=aarch64-linux-gnu- "${@}"
