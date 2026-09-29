#!/bin/bash
# Test plotcake with tmux.
#
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Depends: tmux
#
set -e

session=$(mktemp -u plotcake-XXXXXX)
width=100
heigh=40

cleanup()
{
	tmux kill-session -t ${session}
}
trap cleanup EXIT

tmux new-session -d -s ${session} -x ${width} -y ${heigh} ./plotcake
tmux list-sessions
sleep 0.5

tmux capture-pane -t ${session} -p

tmux send-keys -t ${session} 'v'
tmux capture-pane -t ${session} -p
tmux send-keys -t ${session} 'v'
tmux capture-pane -t ${session} -p

tmux send-keys -t ${session} 'h'
tmux capture-pane -t ${session} -p

tmux send-keys -t ${session} 'l'
tmux capture-pane -t ${session} -p
