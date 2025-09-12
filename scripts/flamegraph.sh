#!/bin/bash
# link: https://github.com/brendangregg/FlameGraph

FLAMEGRAPH_ROOT=/home/rongtao/Git/brendangregg/FlameGraph/

function perf_pid_record()
{
	local pid=$1
	local sec=$2
	echo "Ctrl-C to terminate recor, then generate svg file..."
	sudo perf record -F 99 -p $pid -g -- sleep $sec
}

function flamegraph_gen_svg()
{
	sudo perf script > out.perf
	$FLAMEGRAPH_ROOT/stackcollapse-perf.pl out.perf > out.stack
	$FLAMEGRAPH_ROOT/flamegraph.pl out.stack > out.svg

	echo "Save to out.svg"
}

flamegraph_svg()
{
	if [ $# -lt 2 ]; then
		echo $0 [PID] [Second]
		return 1
	fi

	perf_pid_record $1 $2
	flamegraph_gen_svg
}

flamegraph_svg "$@"
