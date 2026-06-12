#!/bin/bash
set -e

SESSION=tmux-test
TERM_WIDTH=50
TERM_HEIGHT=30

show() {
	tmux capture-pane -t $SESSION -p
}

tmux new-session -d -s $SESSION -x $TERM_WIDTH -y $TERM_HEIGHT
tmux send-keys -t $SESSION top C-m
sleep 0.5

show
tmux send-keys -t "$SESSION" "1"
show
tmux send-keys -t "$SESSION" "q"
show

tmux kill-session -t $SESSION
