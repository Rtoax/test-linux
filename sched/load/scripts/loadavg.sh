#!/bin/bash
# Rong Tao <rongtao@cestc.cn>
# Print Load Average [to file]

date_()
{
	date +%R
}

nr_tasks()
{
	echo `ps -ef | wc -l`
}

load_avg()
{
	load=`cat /proc/loadavg`
	# 89.99 91.24 90.00 7/7062 3562576
	load1=`echo $load | awk '{print $1}'`
	load5=`echo $load | awk '{print $2}'`
	load15=`echo $load | awk '{print $3}'`
	echo "$load1 $load5 $load15"
}

format_5()
{
	echo $@ | \
	awk '{print $1"\t\t"$2"\t\t"$3"\t\t"$4"\t\t"$5}'
}

format_5 "DATE NTask LV1 LV5 LV15"
for ((i=0;;i++))
do
	echo "Loop $i" 1>&2
	format_5 "`date_` `nr_tasks` `load_avg`"
	sleep 10
done
