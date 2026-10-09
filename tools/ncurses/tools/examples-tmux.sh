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

plotcake=$(mktemp ./tmp-plotcake-XXXXXX.sh)
session=$(mktemp -u plotcake-XXXXXX)
width=120
heigh=40

cleanup()
{
	local err=$?
	tmux kill-session -t ${session}
	if [[ ${err} -ne 0 ]]; then
		echo >&2 "ERROR: test failed."
		echo >&2 "--------------------------------------"
		cat >&2 ${plotcake}
		exit ${err}
	else
		rm ${plotcake}
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

check_help_dialog() {
	check_content "\[ HELP \]"
	check_content "\+-\[ HELP \]-----------------------------------\+"
	check_content "\+--------------------------------------------\+"
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
}

check_llabels_dialog() {
	check_content "\[ LINES \]"
	check_content "\+-\[ LINES \]---\+"
	check_content "\+-------------\+"
	check_content "\|------ ${line0}\|"
	check_content "\|------ ${line1}\|"
	check_content "\|------ ${line2}\|"
}

cat >${plotcake}<<EOF
#!/bin/bash
set -e
for ((i = 1; i <= 10000; i++))
do
	seq --separator=' ' \$i 20 \$((i + 2 * 20))
	sleep 0.05
done | ./plotcake --title "${title}" \\
	--xlabel "${xlabel}" \\
	--ylabel "${ylabel}" \\
	--axis-curve-type utf8 \\
	--win-border utf8 \\
	-l "${line0}" -L utf8 \\
	-l "${line1}" -L utf8 \\
	-l "${line2}" -L utf8
EOF
chmod +x ${plotcake}

tmux new-session -d -s ${session} -x ${width} -y ${heigh} ${plotcake}

tmux list-sessions
sleep 0.5

check_content "${title}"
check_content "${ylabel}"
check_content "${line0}"
check_content "${line1}"
check_content "${line2}"
check_content "\^"
check_content "\--------->"

# Turn on the verbose mode
send_keys 'v'

check_content "plot\(redraw=[0-9]+"
check_content "key\(left=[0-9]+"
check_content "enter=0"
check_content "left=0"
check_content "right=0"
check_content "up=0"
check_content "down=0"
check_content "scale 1"
check_content "shft 0\/0"
check_content "$(hostname)"
check_content "1: ${line0}"
check_content "2: ${line1}"
check_content "3: ${line2}"
check_content "<pid:[0-9]+>"

send_keys Enter
send_keys Enter
check_content "enter=2"
send_keys Up
send_keys Up
send_keys Up
check_content "left=0,right=0,up=3,down=0"
check_content "scale 4"
send_keys Down
send_keys Down
send_keys Down
check_content "left=0,right=0,up=3,down=3"
check_content "scale 1"
send_keys Left
send_keys Left
send_keys Left
check_content "left=3,right=0,up=3,down=3"
send_keys Right
send_keys Right
send_keys Right
check_content "left=3,right=3,up=3,down=3"

# Turn off the verbose mode
send_keys 'v'

send_keys 'h'
check_help_dialog

send_keys 'l'
check_llabels_dialog

send_keys 'h'
check_help_dialog

send_keys 'l'
check_llabels_dialog

send_keys Enter

send_keys 't'
check_content "${title} \(signed logarithmic\)"
check_content "s\*log\(1\+"
send_keys 't'
check_content "${title} \(base-10 signed logarithmic\)"
check_content "s\*log10\(1\+"
send_keys 't'
check_content "${title} \(base-e exponential\)"
check_content "exp\("
send_keys 't'
check_content "${title} \(delta\)"
check_content "delta\("
send_keys 't'
send_keys 't' # Back to origin plot type

send_keys 'v'
check_content "h=2"
check_content "l=2"
check_content "t=6"

tmux capture-pane -t ${session} -p
echo "SUCCESS"
