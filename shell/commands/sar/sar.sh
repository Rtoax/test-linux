#!/bin/bash

sar_log_dir=/var/log/sa/

if [[ ! -e ${sar_log_dir} ]]; then
	echo "ERROR: No ${sar_log_dir} exist"
	exit 1
fi

sar_history_logs=( $(ls /var/log/sa/) )

if [[ -z "${sar_history_logs[@]}" ]]; then
	echo "ERROR: No history sar recorded."
	exit 1
fi


# Report paging statistics.
stat_paging()
{
	sar -B -f $1
}

# Report I/O and transfer rate statistics.
stat_IO_rate()
{
	sar -b -f $1
}

# Report system load and pressure-stall statistics.
stat_load()
{
	sar -q -f $1
}

stat_nic()
{
	local iface=ens1f0
	# -n: Report network statistics.
	sar -n ALL -f $1 --iface=${iface}
}

for s in ${sar_history_logs[@]}
do
	f=$sar_log_dir/$s

	stat_paging $f
	stat_IO_rate $f
	stat_load $f
done

