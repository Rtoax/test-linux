#!/bin/bash
# Test bzip2 FDO
# git: git://sourceware.org/git/bzip2.git
#
# 2023-04-19	Rong Tao	Create this
#

test_data=test.dat

run_bzip2()
{
	local b=$1
	local record=$(mktemp record-tmp-XXXXX)
	local real user sys

	rm -f ${test_data}.bz2  || true

	(time ./${b} -z ${test_data} -k) >& ${record}

	real=$(grep ^real ${record} | awk '{print $2}')
	user=$(grep ^user ${record} | awk '{print $2}')

	# 0m6.572s -> 6.572
	real=${real:2:5}
	user=${user:2:5}

	echo -e "${b}\t${real}\t${user}"

	rm -f ${record}
}

# GCC: compile with -fprofile-generate and -fprofile-use to generate fdo binary

dd if=/dev/random of=${test_data} bs=4096 count=30000

echo -e "\tNAME\treal\tuser"
for b in bzip2.orig bzip2.fdo
do
	for ((i = 0; i < 10; i++))
	do
		run_bzip2 ${b}
	done
done

