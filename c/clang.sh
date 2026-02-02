#!/bin/bash
. ../scripts/profile.d/make_tl.sh

# Default: gcc
make_tl CC=clang "${@}"
