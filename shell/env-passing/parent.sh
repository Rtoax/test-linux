#!/bin/bash
set -e

readonly export PARENT_ARGS=( "$@" )

echo "[parent] PARENT_ARGS=${PARENT_ARGS[@]}"

. lib.sh

run_child
