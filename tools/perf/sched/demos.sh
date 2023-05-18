#!/bin/bash

perf_sched_record_latency()
{
	echo "sleep 3"
	sudo perf sched record sleep 3

	sudo perf sched latency
}

