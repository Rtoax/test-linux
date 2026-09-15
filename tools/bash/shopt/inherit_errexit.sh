#!/bin/bash
# Since bash 4.0+ support inherit_errexit
set -eo pipefail
# TODO
# shopt -s inherit_errexit

get_next_id() {
	return 19
}

a=$(get_next_id)
