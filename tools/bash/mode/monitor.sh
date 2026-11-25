#!/bin/bash
# Monitor Mode
# Its let the background process started with & have its own independent process
# group, rather than sharing the same process group with the current script.
set -em

set -o

case "$-" in
*m*)
	echo "enable monitor mode"
	;;
*)
	echo "disable monitor mode"
	exit 1
	;;
esac
