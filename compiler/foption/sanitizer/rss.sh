#!/bin/bash
set -e

comm=thread

get_rss() {
        declare -a PID RSS MAPS TASKS

        PID+=( $(pidof ${comm}) )
        for p in ${PID[@]}
        do
                rss=$(grep Rss /proc/$p/status | awk '{ sum += $2 } END { print sum }')
                RSS+=( ${rss} )
                map=$(wc -l /proc/$p/maps)
                MAP+=( ${map} )
		ntask=$( ls /proc/$p/task/ | wc -w )
		TASKS+=( ${ntask} )
        done

        for ((i = 0; i < ${#PID[@]}; i++))
        do
                printf "$(date '+%Y-%m-%d_%H:%M:%S')\t%-16s %-8d %-16s %-8d %-8d\n" \
                        ${comm} ${PID[$i]} ${RSS[$i]} ${MAP[$i]} ${TASKS[$i]}
        done
}

printf "%-16s\t%-16s %-8s %-16s %-8s %-8s\n" TIME NAME PID RSS MAPS THREADS | tee rss.log
while :; do
        get_rss | tee --append rss.log
        sleep 1
done
