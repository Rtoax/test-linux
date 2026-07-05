#!/bin/bash
set -e

if [[ "${@}" != "PROG_ARGS RRRRRRRRRRRRR TTTTTTTTTTT" ]]; then
	exit 1
fi
