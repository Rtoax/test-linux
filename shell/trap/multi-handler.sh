#!/bin/bash
set -e

exit_handler1() {
	echo "Handler 1"
}

exit_handler2() {
	echo "Handler 2"
}

trap exit_handler1 EXIT
trap exit_handler2 EXIT # Overwrite handle1
