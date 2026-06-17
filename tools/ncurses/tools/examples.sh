#!/bin/bash
# Usage: I=<.1> TMOUT=<1> ./examples.sh

# -m: (set -o monitor) monitor mode
set -em

[[ -z ${I} ]] && I=0.01
[[ -z ${TMOUT} ]] && TMOUT=1

Interval=${I}

args=( --tmout ${TMOUT} )
args+=( ${@} )

# plotcake will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed, just for test in Build.mk's
# `prog-y`.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

line_types=( $(./plotcake -L nonsense 2>/dev/null || true) )

# display all line type
run() {
	while seq --separator=' ' 1 1 ${#line_types[@]}; do
		sleep ${Interval}
	done | ./plotcake ${args[@]} "${@}"
}

run --version
run
run --verbose
run --title 'test title' --xlabel XLABEL --ylabel YLABEL -C red -C red
run $(for t in ${line_types[@]}; do echo "-L ${t}"; done)
run --logarithmic
run --logarithmic10
run --exponential

while true; do
	for i in 2 4 1 4 6 1 9 1 2 3 4 5; do
		seq --separator=' ' 1 1 $i
		sleep ${Interval}
	done
done | ./plotcake ${args[@]}

echo "Byebye"
