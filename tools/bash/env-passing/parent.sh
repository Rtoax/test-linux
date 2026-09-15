#!/bin/bash
set -e

readonly export PARENT_ARGS=( "$@" )

echo "[parent] PARENT_ARGS=${PARENT_ARGS[@]}"

echo PARENT_ARGS=\"${PARENT_ARGS[@]}\" | tee .env

. lib.sh

run_child
