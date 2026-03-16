#!/bin/bash
. ../scripts/make_tl.sh

# Default: gcc
make_tl CC=clang "${@}"
