#!/bin/bash

###############################################################################
open_log() {
	exec 30<> $PWD/tmp.log
}

write_log() {
	echo "$@" >&30
}

close_log() {
	exec 30>&-
}

open_log
write_log "Hello World"
close_log

###############################################################################
start_tracing() {
	set -x
	exec > >(tee $PWD/tmp-2.log) 2>&1
	exec 31> $PWD/tmp-2.log
	BASH_XTRACEFD=31
}
stop_tracing() {
	exec 31>&-
}

start_tracing
echo "Hello World"
stop_tracing
