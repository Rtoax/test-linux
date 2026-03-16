#!/bin/bash
# Default: same as machine
. ../scripts/make_tl.sh
make_tl clean
make_tl M32=1 "${@}"
