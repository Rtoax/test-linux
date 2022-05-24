#!/bin/bash
# Rong Tao <rongtao@cestc.cn>
# Print Load Average [to file]

nr_tasks()
{
	echo `ps -ef | wc -l`
}

load_avg()
{
	load=`cat /proc/loadavg`
	# 89.99 91.24 90.00 7/7062 3562576
	load1=${load: 0: 5}
	load5=${load: 6: 5}
	load15=${load: 12: 5}
	echo "$load1 $load5 $load15"
}

format_4()
{
	echo $@ | \
	awk '{print $1"\t\t"$2"\t\t"$3"\t\t"$4}'
}

format_4 "NTask LV1 LV5 LV15"
for ((i=0;;i++))
do
	format_4 "`nr_tasks` `load_avg`"
	sleep 10
done
