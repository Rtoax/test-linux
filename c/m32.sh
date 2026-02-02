#!/bin/bash
# Default: same as machine
. ../scripts/profile.d/make_tl.sh
make_tl clean
make_tl M32=1 "${@}"
