#!/bin/bash
# Test bzip2 FDO
# git: git://sourceware.org/git/bzip2.git
#
# 2023-04-19	Rong Tao	Create this
#

test_data=test.dat
declare -a orig_record fdo_record

run_bzip2()
{
	local type=$1
	local b=$2
	local record=$(mktemp record-tmp-XXXXX)
	local real user sys

	rm -f ${test_data}.bz2  || true

	(time ./${b} -z ${test_data} -k) >& ${record}

	real=$(grep ^real ${record} | awk '{print $2}')
	user=$(grep ^user ${record} | awk '{print $2}')

	# 0m6.572s -> 6.572
	real=${real:2:5}
	user=${user:2:5}

	if [[ $type == orig ]]; then
		orig_record+=( ${user} )
	else
		fdo_record+=( ${user} )
	fi

	echo -e "${b}\t${real}\t${user}"

	rm -f ${record}
}

# GCC: compile with -fprofile-generate and -fprofile-use to generate fdo binary

dd if=/dev/random of=${test_data} bs=4096 count=30000

num=10
echo -e "\tNAME\treal\tuser"
for ((i = 0; i < ${num}; i++))
do
	run_bzip2 orig bzip2.orig
	run_bzip2 fdo bzip2.fdo
done

# Print results
echo -e "NUM\tOrig\tFDO"
for ((i = 0; i < ${num}; i++))
do
	echo -e "${i}\t${orig_record[$i]}\t${fdo_record[$i]}"
done
