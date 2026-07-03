#!/bin/bash
set -e

scale() {
	# -k: keep after quit
	# -t: Delay seconds
	# -s scale: scale mode
	ncplayer -t 0.5 -s scale ${@}
}

scale ../../../gnu/gnu.webp
scale ../../../bpf/cilium/cilium.png
scale ../../../Documentation/images/logo.svg
