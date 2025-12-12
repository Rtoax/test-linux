#!/bin/bash
# see also iostat of https://github.com/sysstat/sysstat
set -e

SYSFS="/sys/block/"
BLOCK=( $(ls ${SYSFS}) )


for blk in ${BLOCK[@]}
do
	_ios_pgr= _tot_ticks= _rq_ticks= _wr_ticks= _dc_ticks= _fl_ticks=
	_rd_ios= _rd_merges_or_rd_sec= _wr_ios= _wr_merges=
	_rd_sec_or_wr_ios= _wr_sec= _rd_ticks_or_wr_sec=
	_dc_ios= _dc_merges= _dc_sec= _fl_ios=

	stat="${SYSFS}/${blk}/stat"
	values=( $(cat ${stat}) )

	_rd_ios=${values[0]}
	_rd_merges_or_rd_sec=${values[1]}
	_rd_sec_or_wr_ios=${values[2]}
	_rd_ticks_or_wr_sec=${values[3]}
	_wr_ios=${values[4]}
	_wr_merges=${values[5]}
	_wr_sec=${values[6]}
	_wr_ticks=${values[7]}
	_ios_pgr=${values[8]}
	_tot_ticks=${values[9]}
	_rq_ticks=${values[10]}
	_dc_ios=${values[11]}
	_dc_merges=${values[12]}
	_dc_sec=${values[13]}
	_dc_ticks=${values[14]}
	_fl_ios=${values[15]}
	_fl_ticks=${values[16]}

	if [[ ${#values[@]} -ge 11 ]]; then
		rd_ios=$_rd_ios
		rd_merges=$_rd_merges_or_rd_sec
		rd_sectors=$_rd_sec_or_wr_ios
		rd_ticks=$rd_ticks
		wr_ios=$_wr_ios
		wr_merges=$_wr_merges
		wr_ticks=$_wr_ticks
		ios_pgr=$_ios_pgr
		tot_ticks=$_tot_ticks
		rq_ticks=$_rq_ticks

		if [[ ${#values[@]} -ge 15 ]]; then
			dc_ios=$_dc_ios
			dc_merges=$_dc_merges
			dc_sectors=$_dc_sec
			dc_ticks=$_dc_ticks
		fi

		if [[ ${#values[@]} -ge 15 ]]; then
			fl_ios=$_fl_ios
			fl_ticks=$_fl_ticks
		fi
	elif [[ ${#values[@]} -eq 4 ]]; then
		rd_ios=$_rd_ios
		rd_sectors=$_rd_merges_or_rd_sec
		wr_ios=$_rd_sec_or_wr_ios
		wr_sectors=$_rd_ticks_or_wr_sec
	fi
done
