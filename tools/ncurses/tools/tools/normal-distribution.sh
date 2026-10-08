#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols 2>/dev/null || echo 80)

python3 -c '
import numpy as np
import sys

mu, sigma = 0, 1
k = 4
lo, hi = mu - k*sigma, mu + k*sigma
n = int(sys.argv[1])

x = np.linspace(lo, hi, n)
pdf = np.exp(-(x-mu)**2/(2*sigma**2)) / (sigma*np.sqrt(2*np.pi))

for xi, pi in zip(x, pdf):
	print(f"{xi:.6f}\t{pi:.6f}")
' $((${cols} - 9)) | awk '{print $2}' | \
	${PLOTCAKE} --title "Normal Distribution" -o normal-distribution --x-index "${@}"
