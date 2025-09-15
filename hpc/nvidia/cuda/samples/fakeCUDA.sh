#!/bin/bash
set -e

FAKECUDA_ROOT=$PWD/../fakeCUDA
make -C ${FAKECUDA_ROOT} --no-print-directory --silent 1>/dev/null

LD_LIBRARY_PATH=${FAKECUDA_ROOT} "./$@"
