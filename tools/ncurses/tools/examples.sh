#!/bin/bash
# -m: (set -o monitor) monitor mode
set -em

args=( --tmout 2 )

# plotcake will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed, just for test in Build.mk's
# `prog-y`.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

# display all line type
all_line_type() {
	while sleep 0.05; do
		seq 1 1 $(./plotcake -L nonsense 2>/dev/null | wc -l)
	done | ./plotcake ${args[@]} $(./plotcake -L nonsense 2>/dev/null | sed 's/^/-L/g') \
		-C red -C red ${@}
}
all_line_type
all_line_type --logarithmic
all_line_type --logarithmic10

#
for i in 2 4 1 4 6 1 9; do
	seq 1 1 $i
	sleep .1
done | ./plotcake ${args[@]}

echo "Byebye"
