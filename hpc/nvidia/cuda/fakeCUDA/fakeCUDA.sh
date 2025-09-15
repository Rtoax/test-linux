#!/bin/bash
set -e

readonly FAKECUDA_ROOT=$(dirname $(readlink $0))
make -C ${FAKECUDA_ROOT} --no-print-directory --silent 1>/dev/null

LD_LIBRARY_PATH=${FAKECUDA_ROOT} "$@"
