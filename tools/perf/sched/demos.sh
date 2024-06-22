#!/bin/bash

perf_sched_record_latency()
{
	# Record sched
	sudo perf sched record sleep 3
	# Show latency
	sudo perf sched latency
}

