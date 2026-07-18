#!/bin/bash
# stty rows 24 cols 80 && ncplayer ...
# resize -s 80 24 && ncplayer ...
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
