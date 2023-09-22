#!/bin/bash 

set -euo pipefail

function dmesg_tail() {
	dmesg | tail -n 20
}
function dmesg_kernel_tail() {
	dmesg -k | tail -n 20
}
dmesg_tail
