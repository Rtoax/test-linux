#!/bin/bash
set -e

[[ -z ${LOGS} ]] && LOGS=( $(ls gdsio-x*.log) )

for log in ${LOGS[@]}
do
	txt=${log%.*}.txt
	cat ${log} | awk '{
		for (i=1; i<=NF; i++) {
			if ($i == "IoType:") {
				gsub(/,/, "", $(i+1));
				iotype=$(i+1);
			}
			if ($i == "Threads:") {
				# remove ','
				gsub(/,/, "", $(i+1));
				threads=$(i+1)
			}
			if ($i == "IOSize:") {
				iosize=$(i+1);
			}
			if ($i == "Throughput:") {
				throughput=$(i+1);
			}
		}
		printf("%s %s %s\n", iosize / 1024, threads, throughput);
	}' | tee ${txt}
done
