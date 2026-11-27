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
legend0="Legend 0"
legend1="Legend 1"
legend2="Legend 2"

plotcake=$(mktemp ./tmp-plotcake-XXXXXX.sh)
session=$(mktemp -u plotcake-XXXXXX)
width=150
heigh=40
vertical_plotting=
stdin_data_format=
readonly STDIN_DATA_FMTS=(
	# default is line-no-separator
	line-separator-newline
	line-separator-semicolon
	scatter-no-separator
)
skip_cleanup=

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/tools/lib-plotcake.sh

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    plotcake-examples-tmux - Test plotcake with tmux

${BOLD}SYNOPSIS${RST}
    plotcake-examples-tmux [opts]

${BOLD}OPTIONS${RST}
    --vertical-plotting           test plotcake vertical plotting
    --stdin-data-format [FORMAT]  test stdint data format: '${STDIN_DATA_FMTS[@]}'
    --skip-cleanup                skip cleanup
    -h, --help                    show this information
"
	exit ${1-0}
}

OPTS=$(getopt --options h \
		--long help \
		--long vertical-plotting \
		--long stdin-data-format: \
		--long skip-cleanup \
		--name plotcake-examples-tmux -- "$@")

eval set -- "$OPTS"

while true; do
	case $1 in
	--vertical-plotting)
		shift
		vertical_plotting=ON
		;;
	--stdin-data-format)
		shift
		if ! [[ " ${STDIN_DATA_FMTS[@]} " =~ " ${1} " ]]; then
			echo >&2 "ERROR: bad --stdin-data-format '${1}'"
			exit 1
		fi
		stdin_data_format=${1}
		shift
		;;
	--skip-cleanup)
		shift
		skip_cleanup=ON
		;;
	-h | --help)
		shift
		__usage__
		;;
	--)
		shift
		break
		;;
	esac
done

is_scatter() {
	if [[ ${stdin_data_format} =~ scatter ]]; then
		echo YES
		return 0
	fi
	return 1
}

is_line() {
	if [[ -z ${stdin_data_format} ]] ||
	   [[ ${stdin_data_format} =~ line- ]]; then
		echo YES
		return 0
	fi
	return 1
}

kill_session() {
	tmux kill-session -t ${session} || true
}

cleanup()
{
	local err=$?
	kill_session
	if [[ ${err} -ne 0 ]]; then
		echo >&2 "ERROR: test failed."
		echo >&2 "--------------------------------------"
		cat >&2 ${plotcake}
		exit ${err}
	else
		if [[ -z ${skip_cleanup} ]]; then
			rm ${plotcake}
		fi
	fi
}
trap cleanup EXIT

send_keys() {
	tmux send-keys -t ${session} "${@}"
}

capture_pane() {
	tmux capture-pane -t ${session} -p
}

check_content() {
	local pattern="${@}"
	local pane="$(capture_pane)"
	local match="$(echo -e "${pane}" | grep -oE "${pattern}")"
	if [[ -z "${match}" ]]; then
		echo -e >&2 "\033[1;31mERROR: pattern '${pattern}' was not matched in:\033[m\n\n'${pane}'"
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
	check_content "'s': enable/disable stacked line chart"
	check_content "'t': change numerical scaling type for paint"
	check_content "'v': turn on/off the verbose mode"
	check_content "'x': switch x axis type"
}

check_legends_dialog() {
	if [[ $(is_line) ]]; then
		check_content "\[ LINES \]"
		check_content "\+-\[ LINES \]------\+"
		check_content "\|------ ${legend0} \|"
		check_content "\|------ ${legend1} \|"
		check_content "\|------ ${legend2} \|"
		check_content "\+----------------\+"
	elif [[ $(is_scatter) ]]; then
		check_content "\[ SCATTER \]"
		check_content "\+-\[ SCATTER \]---\+"
		check_content "\|. ${legend0}     \|"
		check_content "\|. ${legend1}     \|"
		check_content "\|. ${legend2}     \|"
		check_content "\+---------------\+"
	fi
}

cat >${plotcake}<<EOF
#!/bin/bash
set -e
interval=1
case "${stdin_data_format}" in
line-separator-newline | line-separator-semicolon | scatter-no-separator)
	interval=3
	;;
esac
for ((i = 1; i <= 10000; i+=interval))
do
	case "${stdin_data_format}" in
	line-separator-newline | line-separator-semicolon)
		data1=( \$(seq --separator=' ' \$i 20 \$((i + 2 * 20))) )
		j=\$((i + 1))
		data2=( \$(seq --separator=' ' \$j 20 \$((j + 2 * 20))) )
		j=\$((j + 1))
		data3=( \$(seq --separator=' ' \$j 20 \$((j + 2 * 20))) )
		case "${stdin_data_format}" in
		line-separator-newline)
			echo -e "\${data1[@]}\\n\${data2[@]}\\n\${data3[@]}\\n"
			;;
		line-separator-semicolon)
			echo -e "\${data1[@]};\${data2[@]};\${data3[@]};"
			;;
		esac
		;;
	scatter-no-separator)
		j=\$((i + 1))
		k=\$((i + 2))
		echo "(\${i},\${i}) (\${j}, \${j}) (\${k}, \${k})"
		;;
	# line-no-separator
	*)
		seq --separator=' ' \$i 20 \$((i + 2 * 20))
		;;
	esac
	sleep 0.05
done | ${PLOTCAKE} ${vertical_plotting:+--vertical-plotting} \\
	--title "${title}" \\
	--xlabel "${xlabel}" \\
	--ylabel "${ylabel}" \\
	--axis-curve-type utf8 \\
	--win-border utf8 \\
	-l "${legend0}" -D utf8 \\
	-l "${legend1}" -D utf8 \\
	-l "${legend2}" -D utf8
EOF
chmod +x ${plotcake}

tmux new-session -d -s ${session} -x ${width} -y ${heigh} ${plotcake}

tmux list-sessions
sleep 0.5

check_content "${title}"
check_content "${ylabel}"
if [[ $(is_line) ]]; then
	check_content "${legend0}"
	check_content "${legend1}"
	check_content "${legend2}"
elif [[ $(is_scatter) ]]; then
	if [[ ${vertical_plotting} ]]; then
		# The printed numbers are obscured.
		check_content "\(16\..00,16\.000\)"
	else
		check_content "\(16\.000,16\.000\)"
	fi
else
	capture_pane
	echo >&2 "ERROR: '${stdin_data_format}' is neither line nor scatter"
	exit 1
fi
if [[ ${vertical_plotting} ]]; then
	check_content "\`"
else
	check_content "\^"
fi
check_content "\--------->"

# Turn on the verbose mode
send_keys 'v'

if [[ $(is_line) ]]; then
	check_content "lgroup cnt 3, arg nline 3"
elif [[ $(is_scatter) ]]; then
	check_content "scatter cnt 3"
fi

check_content "plot\(redraw=[0-9]+"
check_content "key\(left=[0-9]+"
check_content "enter=0"
check_content "left=0"
check_content "right=0"
check_content "up=0"
check_content "down=0"
if [[ $(is_line) ]]; then
	check_content "scale 1"
	check_content "shft 0/0"
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
check_content "$(hostname)"
check_content "1: ${legend0}"
check_content "2: ${legend1}"
check_content "3: ${legend2}"
check_content "<pid:[0-9]+>"

send_keys Enter
send_keys Enter
check_content "enter=2"
send_keys Up
send_keys Up
send_keys Up
check_content "left=0,right=0,up=3,down=0"
if [[ $(is_line) ]]; then
	check_content "scale 4"
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
send_keys Down
send_keys Down
send_keys Down
check_content "left=0,right=0,up=3,down=3"
if [[ $(is_line) ]]; then
	check_content "scale 1"
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
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
check_legends_dialog

send_keys 'h'
check_help_dialog

send_keys 'l'
check_legends_dialog

send_keys Enter

send_keys 's'
check_content "[stacked]"
send_keys 's'

send_keys 't'
check_content "${title} \(signed logarithmic\)"
if [[ $(is_line) ]]; then
	check_content "s\*log\(1\+"
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
send_keys 't'
check_content "${title} \(base-10 signed logarithmic\)"
if [[ $(is_line) ]]; then
	check_content "s\*log10\(1\+"
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
send_keys 't'
check_content "${title} \(base-e exponential\)"
if [[ $(is_line) ]]; then
	check_content "exp\("
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
send_keys 't'
check_content "${title} \(delta\)"
if [[ $(is_line) ]]; then
	check_content "delta\("
elif [[ $(is_scatter) ]]; then
	echo -n # TODO
fi
send_keys 't'
send_keys 't' # Back to origin plot type

send_keys 'x'
if [[ ${vertical_plotting} ]]; then
	check_content "1"
	check_content "2"
	check_content "9"
else
	if [[ $(is_line) ]]; then
		check_content "1[[:space:]]+11" # '+' for multi whitespace
	elif [[ $(is_scatter) ]]; then
		echo -n # TODO
	fi
fi

# Turn on the verbose mode
send_keys 'v'
check_content "h=2"
check_content "l=2"
check_content "s=2"
check_content "t=6"
check_content "x=1"

capture_pane

kill_session
plotcake_reset

echo "==========vertical_plotting=${vertical_plotting}"
echo "==========stdin_data_format=${stdin_data_format}"
echo "==========skip_cleanup=${skip_cleanup}"
echo -e "==========\033[1;32mSUCCESS\033[m"
