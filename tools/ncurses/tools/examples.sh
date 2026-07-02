#!/bin/bash
# Usage: I=<0.1> TMOUT=<1s> ./examples.sh

# -m: (set -o monitor) monitor mode
set -em
readonly PLOTCAKE=./plotcake

[[ -z ${I} ]] && I=0.001
[[ -z ${TMOUT} ]] && TMOUT=200ms

Interval=${I}

args=( -t ${TMOUT} --tmout ${TMOUT} )
args+=( -v --verbose )
args+=( ${@} )

# plotcake will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed, just for test in Build.mk's
# `prog-y`.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

readonly line_types=( $(${PLOTCAKE} -L nonsense 2>/dev/null || true) )

run() {
	${PLOTCAKE} ${args[@]} -I 10ms --interval=10ms "${@}"
}

stdin() {
	while seq --separator=' ' 1 1 ${#line_types[@]}; do
		sleep ${Interval}
	done | ${PLOTCAKE} ${args[@]} "${@}"
}

run -? --help
run --usage
run -V --version
run -M --ram
run -o data
run -f data.txt

stdin -V --version
stdin --usage
stdin --title 'test title' --xlabel XLABEL --ylabel YLABEL -C red -C red
stdin $(for t in ${line_types[@]}; do echo "-L ${t}"; done)
stdin --logarithmic
stdin --logarithmic10
stdin --exponential

while true; do
	for i in 2 4 1 4 6 1 9 1 2 3 4 5; do
		seq --separator=' ' 1 1 $i
		sleep ${Interval}
	done
done | ${PLOTCAKE} ${args[@]}

echo "Byebye"
