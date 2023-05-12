#!/bin/bash
# Test gzip/gunzip FDO
# git: https://git.savannah.gnu.org/git/gzip.git
#
# 2023-04-19	Rong Tao	Create this
#

test_data=test.dat
declare -a orig_record fdo_record

run_gzip()
{
	local type=$1
	local b=$2
	local record=$(mktemp record-tmp-XXXXX)
	local real user sys

	rm -f ${test_data}.gz  || true

	(time ./${b} ${test_data} -k) >& ${record}

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

# Compile
#
# GCC Native:
#  CFLAGS += -fprofile-generate
#  CFLAGS += -fprofile-use
#
# GCC AutoFDO
#  perf record -b -e br_inst_retired.near_taken:pp -- ./gzip
#  create_gcov \
#		--binary=./gzip \
#		--profile=perf.data \
#		--gcov=gzip.gcov \
#		-gcov_version=1 >/dev/null
#  gcc -fauto-profile=gzip.gcov ...
#
# Clang:
#  CFLAGS += -fprofile-generate
#  llvm-profdata merge --output profile.profdata default*.profraw
#  CFLAGS += -fprofile-use=profile.profdata

dd if=/dev/random of=${test_data} bs=4096 count=100000

num=10
echo -e "\tNAME\treal\tuser"
for ((i = 0; i < ${num}; i++))
do
	run_gzip orig gzip.orig
	run_gzip fdo gzip.fdo
done

# Print results
echo -e "NUM\tOrig\tFDO"
for ((i = 0; i < ${num}; i++))
do
	echo -e "${i}\t${orig_record[$i]}\t${fdo_record[$i]}"
done
