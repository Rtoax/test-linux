#!/bin/bash
set -e

. ../scripts/make_tl.sh
make_tl DEBUG=1 "${@}"
