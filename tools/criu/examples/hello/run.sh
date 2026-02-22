#!/bin/bash

log() {
	echo -e "\033[32m$@\033[m"
}

log "Compiling..."
gcc hello.c -o a.out

./a.out &
log "Running in background, pid = $(pidof a.out)..."
sleep 3

log "Dump to imgdir..."
test ! -e imgdir && mkdir imgdir
sudo criu dump -D imgdir/ -j -t $(pidof a.out)

log "Wait for 3 seconds..."
tree imgdir
sleep 3

sudo criu restore --restore-detached -D imgdir/ -j
log "Restore process and continue running, pid = $(pidof a.out)..."
sleep 3

log "Exit..."
test -e imgdir && rm -rf imgdir
pkill a.out

