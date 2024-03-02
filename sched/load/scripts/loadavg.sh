#!/bin/bash
# Rong Tao <rtoax@foxmail.com>
# Print Load Average [to file]
# Like 'sar -q ALL'

date_()
{
	date +%R
}

nr_tasks()
{
	echo `ps -ef | wc -l`
}

nr_R_tasks()
{
	ps -e -w -o stat,pid,lstart,comm | grep ^R | wc -l
}

nr_S_tasks()
{
	ps -e -w -o stat,pid,lstart,comm | grep ^S | wc -l
}

nr_D_tasks()
{
	ps -e -w -o stat,pid,lstart,comm | grep ^D | wc -l
}

nr_threads()
{
	echo `ps -efL | wc -l`
}

nr_R_threads()
{
	ps -e -w -L -o stat,pid,lstart,comm | grep ^R | wc -l
}

nr_S_threads()
{
	ps -e -w -L -o stat,pid,lstart,comm | grep ^S | wc -l
}

nr_D_threads()
{
	ps -e -w -L -o stat,pid,lstart,comm | grep ^D | wc -l
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

format_output()
{
	echo $@ | \
	awk '{print $1"\t\t"$2"\t\t"$3"\t\t"$4"\t\t"$5"\t\t"$6"\t\t"$7"\t\t"$8"\t\t"$9"\t\t"$10"\t\t"$11"\t\t"$12}'
}

statistic_loadavg()
{
	format_output "DATE NTask DTask RTask STask NThread DThread RThread SThread LV1 LV5 LV15"
	for ((i=0;;i++))
	do
		echo "Loop $i" 1>&2
		format_output "`date_` \
			`nr_tasks` `nr_D_tasks` `nr_R_tasks` `nr_S_tasks` \
			`nr_threads` `nr_D_threads` `nr_R_threads` `nr_S_threads` \
			`load_avg`"
		sleep 60
	done
}

statistic_loadavg
