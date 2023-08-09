#!/bin/bash

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
