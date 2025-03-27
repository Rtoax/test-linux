#!/bin/bash
set -e

_eval() {
	eval "$@"
}

_eval ls < /etc/os-release
