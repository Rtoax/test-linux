#!/bin/bash
set -e

. ../scripts/profile.d/make_tl.sh
make_tl DEBUG=1 "${@}"
