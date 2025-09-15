#!/bin/bash
set -e

FAKECUDA_ROOT=$PWD/../fakeCUDA
make -C ${FAKECUDA_ROOT}

LD_LIBRARY_PATH=${FAKECUDA_ROOT} "$@"
