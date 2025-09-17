#!/bin/bash
set -e

[[ ${FAKECUDA_DEBUG} ]] && set -x

readonly FAKECUDA_ROOT=$(realpath $(dirname $(readlink $0)))
make -C ${FAKECUDA_ROOT} --no-print-directory --silent 1>/dev/null

[[ -f $1 ]] && [[ -x $1 ]] && PREFIX=./

LD_LIBRARY_PATH=${FAKECUDA_ROOT} "${PREFIX}$@"
