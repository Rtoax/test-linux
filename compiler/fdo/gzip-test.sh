#!/bin/bash
# Test gzip/gunzip FDO
# git: https://git.savannah.gnu.org/git/gzip.git
#
# 2023-04-19	Rong Tao	Create this
# 2023-05-12	Rong Tao	Support autofdo
# 2023-05-15	Rong Tao	Support llvm-bolt
#

test_data=test.dat
declare -a orig_record fdo_record autofdo_record bolt_record

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
	elif [[ $type == fdo ]]; then
		fdo_record+=( ${user} )
	elif [[ $type == autofdo ]]; then
		autofdo_record+=( ${user} )
	elif [[ $type == bolt ]]; then
		bolt_record+=( ${user} )
	fi

	echo -e "${b}\t${real}\t${user}"

	rm -f ${record}
}

# Compile
#
# GCC Native:
#  CFLAGS += -fprofile-generate
#  gcc ... ${CFLAGS} -o gzip.orig
#  CFLAGS += -fprofile-use
#  gcc ... ${CFLAGS} -o gzip.fdo
#
# GCC AutoFDO
#  gcc ... -o gzip.gcc.orig
#  perf record -b -e br_inst_retired.near_taken:pp -- ./gzip.gcc.orig -k test.dat
#  create_gcov \
#		--binary=./gzip \
#		--profile=perf.data \
#		--gcov=gzip.gcov \
#		-gcov_version=1 >/dev/null
#  LDFLAGS += -fauto-profile=gzip.gcov
#  gcc ... ${LDFLAGS} -o gzip.gcc.autofdo
#
# LLVM BOLT
#  perf record -e cycles:u -j any,u -o perf.data -- ./gzip.gcc.orig -k test.dat
#  llvm-bolt gzip.gcc.orig -o gzip.gcc.bolt \
#    -data=perf.data -reorder-blocks=ext-tsp -split-functions \
#    -split-all-cold -split-eh -dyno-stats
#
# Clang:
#  CFLAGS += -fprofile-generate
#  gcc ... ${CFLAGS} -o gzip.orig
#  llvm-profdata merge --output profile.profdata default*.profraw
#  CFLAGS += -fprofile-use=profile.profdata
#  gcc ... ${CFLAGS} -o gzip.fdo

dd if=/dev/random of=${test_data} bs=4096 count=100000

num=10
echo -e "\n\tNAME\treal\tuser"
for ((i = 0; i < ${num}; i++))
do
	run_gzip orig gzip.orig
	run_gzip fdo gzip.fdo
	[[ -e gzip.autofdo ]] && run_gzip autofdo gzip.autofdo
	[[ -e gzip.bolt ]] && run_gzip bolt gzip.bolt
done

# Print results
echo
echo -e "NUM\tOrig\tFDO\tAutoFDO\tBOLT"
for ((i = 0; i < ${num}; i++))
do
	echo -e "${i}\t${orig_record[$i]}\t${fdo_record[$i]}\t${autofdo_record[$i]}\t${bolt_record[$i]}"
done
