#!/bin/bash
. ../scripts/profile.d/make_tl.sh
make_tl clean
make_tl STATIC=1 "${@}"
