#!/bin/bash
set -e

scale() {
	ncplayer -t 0.5 -s scale ${@}
}

scale ../../../gnu/gnu.webp
scale ../../../bpf/cilium/cilium.png
scale ../../../Documentation/images/logo.svg
