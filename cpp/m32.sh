#!/bin/bash
. ../scripts/make_tl.sh

# Default: same as machine
make_tl clean
make_tl M32=1 "${@}"
