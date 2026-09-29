#!/bin/bash
# Test plotcake with tmux.
#
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Depends: tmux
#
set -e

title="This is Title"
xlabel="Axis X"
ylabel="Axis Y"
line0="Line 0"
line1="Line 1"
line2="Line 2"

session=$(mktemp -u plotcake-XXXXXX)
width=120
heigh=40

cleanup()
{
	local err=$?
	tmux kill-session -t ${session}
	if [[ ${err} -ne 0 ]]; then
		echo >&2 "ERROR: test failed."
		exit ${err}
	fi
}
trap cleanup EXIT

send_keys() {
	tmux send-keys -t ${session} "${@}"
}

check_content() {
	local pattern="${@}"
	local pane="$(tmux capture-pane -t ${session} -p)"
	local match="$(echo -e "${pane}" | grep -oE "${pattern}")"
	if [[ -z "${match}" ]]; then
		echo -e >&2 "\033[1;31mERROR: pattern '${pattern}' was not matched in \033[m'${pane}'"
		exit 1
	fi
}

tmux new-session -d -s ${session} -x ${width} -y ${heigh} \
	./plotcake --title "${title}" \
		--xlabel "${xlabel}" \
		--ylabel "${ylabel}" \
		-l "${line0}" \
		-l "${line1}" \
		-l "${line2}" \
		--interval 100ms

tmux list-sessions
sleep 0.5

check_content "${title}"
check_content "${ylabel}"
check_content "${line0}"
check_content "${line1}"
check_content "${line2}"

# Turn on the verbose mode
send_keys 'v'

check_content "plot\(redraw=[0-9]+"
check_content "key\(left=[0-9]+"
check_content "$(hostname)"
check_content "1: ${line0}"
check_content "2: ${line1}"
check_content "3: ${line2}"
check_content "<pid:[0-9]+>"

# Turn off the verbose mode
send_keys 'v'

send_keys 'h'
check_content "\[ HELP \]"
check_content "Enter: refresh plot"
check_content "Up: uniform scaling up"
check_content "Down: uniform scaling down"
check_content "Left: curve shifts to the right"
check_content "Right: curve shifts to the left"
check_content "'h': show the help info"
check_content "'l': show the label for each line"
check_content "'q': quit the plotcake"
check_content "'r': reset the ploting"
check_content "'t': change numerical scaling type for paint"
check_content "'v': turn on/off the verbose mode"

send_keys 'l'
check_content "\[ LINES \]"
check_content " ${line0}"
check_content " ${line1}"
check_content " ${line2}"
