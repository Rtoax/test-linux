#!/bin/bash

set -e

PROGs=(
	basic-vm
	cpuid
	hello
	load-payload01
	protected-mode-with-paging
	exceptions
	ia32e-paging
	load-payload02
)

make

for p in ${PROGs[@]}
do
	echo -e "\033[1;32m=== $p ===\033[m"
	./${p}
done

echo "=== Done."
