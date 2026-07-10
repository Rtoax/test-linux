#!/bin/bash
set -e

scale() {
	# -k: keep after quit
	# -t: Delay seconds
	# -s scale: scale mode
	ncplayer -t 0.5 -s scale ${@}
}

scale ../../../Documentation/images/cilium.png
scale ../../../Documentation/images/ebpf.png
scale ../../../Documentation/images/gnu.webp
scale ../../../Documentation/images/tux.svg
