#!/bin/bash
# Default: same as machine
make clean
make M32=1 "${@}"
