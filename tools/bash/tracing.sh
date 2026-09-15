#!/bin/bash

start_tracing() {
	set -x
	exec > >(tee $PWD/tmp-2.log) 2>&1
	# open file fd=31
	exec 31> $PWD/tmp-2.log
	BASH_XTRACEFD=31
}
stop_tracing() {
	exec 31>&-
}

start_tracing
echo "Hello World"
cat /etc/os-release
stop_tracing

echo ----------------------------
cat tmp-2.log
