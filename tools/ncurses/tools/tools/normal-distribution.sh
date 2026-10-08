#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols)

python3 -c '
import numpy as np
import sys
x = np.linspace(-4, 4, int(sys.argv[1]))
pdf = np.exp(-x**2/2) / np.sqrt(2*np.pi)
for xi, pi in zip(x, pdf):
	print(f"{xi:.6f}\t{pi:.6f}")
' $((${cols} - 9)) | awk '{print $2}' | \
	${PLOTCAKE} --title "Normal Distribution" -o normal-distribution --x-index "${@}"
