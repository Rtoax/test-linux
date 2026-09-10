#!/bin/bash
set -e

var1=1

exit_handler() {
	# print 2
	echo "var1=${var1}"
}

trap exit_handler EXIT

var1=2
