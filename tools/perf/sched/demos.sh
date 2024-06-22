#!/bin/bash

perf_sched_record_latency()
{
	# Record sched for seconds
	sudo perf sched record -- sleep 5
	# Show latency sort by max value
	sudo perf sched latency --sort max
}

