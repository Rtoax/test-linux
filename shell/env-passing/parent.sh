#!/bin/bash
set -e

readonly export PARENT_ARGS=( "$@" )

. parent-lib.sh

run_child
