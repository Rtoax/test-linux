#!/bin/bash
set -e

run_child() {
	echo "[lib] PARENT_ARGS=${PARENT_ARGS[@]}"
	./child.sh "$@"
}
