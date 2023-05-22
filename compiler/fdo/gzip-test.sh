#!/bin/bash
# Test gzip/gunzip FDO
# git: https://git.savannah.gnu.org/git/gzip.git
#
# 2023-04-19	Rong Tao	Create this
# 2023-05-12	Rong Tao	Support autofdo
# 2023-05-15	Rong Tao	Support llvm-bolt
# 2023-05-19	Rong Tao	Auto compile original/fdo/autofdo
#

set -e

verbose=

test_data=data.bin
declare -a orig_record fdo_record autofdo_record bolt_record

run_gzip()
{
	local type=$1
	local b=$2
	local record=$(mktemp record-tmp-XXXXX)
	local real user sys

	rm -f ${test_data}.gz  || true

	(time taskset -c 2 ./${b} ${test_data} -k) >& ${record}

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
#  make clean
#  make CFLAGS=-fprofile-generate
#  ./gzip -k data.bin
#  make clean
#  make CFLAGS=-fprofile-use or
#  make CFLAGS="-fprofile-use -Wno-missing-profile -Wno-suggest-attribute=cold"
#
# GCC AutoFDO
#  gcc ... -o gzip.gcc.orig
#  perf record -b -e br_inst_retired.near_taken:pp -- ./gzip.gcc.orig -k data.bin
#  create_gcov \
#		--binary=./gzip \
#		--profile=perf.data \
#		--gcov=gzip.gcov \
#		-gcov_version=1 >/dev/null
#  CFLAGS += -fauto-profile=gzip.gcov
#  LDFLAGS += -fauto-profile=gzip.gcov
#  gcc ... ${LDFLAGS} -o gzip.gcc.autofdo
#
# LLVM BOLT
#  perf record -e cycles:u -j any,u -o perf.data -- ./gzip.gcc.orig -k data.bin
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

gcov_dir=GCOVs

gen_gcov_dir()
{
	if [[ ! -e ${gcov_dir} ]]; then
		mkdir ${gcov_dir}
	fi
}

clean_gcov()
{
	rm -fr \
		$(find -name '*.gcov') \
		$(find -name '*.gcda')
}

gen_test_data()
{
	if [[ ! -e data.bin ]]; then
		dd if=/dev/random of=${test_data} bs=4096 count=100000
	fi
}

clean_tmp()
{
	rm -fr \
		data.bin.gz \
		perf.data
}

clean_exe()
{
	set -x
	rm -fr \
		gzip.orig \
		gzip.fdo \
		gzip.afdo \
		gzip.bolt
	set +x
}

clean_git()
{
	git clean -dfx \
		-e ${gcov_dir} \
		-e test.sh \
		-e gzip.orig \
		-e gzip.fdo \
		-e gzip.afdo
}

configure_makefile()
{
	make ${verbose:+V=1} clean || true
	clean_git

	./bootstrap
	./configure

	sed -i 's/^CFLAGS =/CFLAGS = $(RT_CFLAGS) /g' Makefile
	sed -i 's/^LDFLAGS =/LDFLAGS = $(RT_LDFLAGS) /g' Makefile
}

compile_orig()
{
	configure_makefile

	make ${verbose:+V=1} clean
	clean_tmp

	make ${verbose:+V=1}

	mv gzip gzip.orig
}

compile_fdo()
{
	gen_gcov_dir

	configure_makefile
	make ${verbose:+V=1} clean
	clean_tmp
	clean_gcov

	make ${verbose:+V=1} RT_CFLAGS=-fprofile-generate=${gcov_dir}

	gen_test_data

	./gzip -k data.bin

	configure_makefile
	make ${verbose:+V=1} clean

	make ${verbose:+V=1} RT_CFLAGS="-fprofile-use=${gcov_dir} -Wno-missing-profile -Wno-suggest-attribute=cold"

	mv gzip gzip.fdo
}

compile_autofdo()
{
	local autofdo_all_branch_retired=

	while :;
	do
		case $1 in
		--br-all)
			shift
			autofdo_all_branch_retired=YES
			;;
		*)
			break
			;;
		esac
	done

	configure_makefile
	make ${verbose:+V=1} clean
	clean_tmp

	make ${verbose:+V=1}

	gen_test_data

	# perf list : pipeline
	local branches_retired=(
		br_inst_retired.all_branches
		br_inst_retired.all_branches_pebs
		br_inst_retired.cond_ntaken
		br_inst_retired.conditional
		br_inst_retired.far_branch
		br_inst_retired.near_call
		br_inst_retired.near_return
		# AutoFDO Default
		# br_inst_retired.near_taken
		br_inst_retired.not_taken
		br_misp_retired.all_branches
		br_misp_retired.all_branches_pebs
		br_misp_retired.conditional
		br_misp_retired.near_call
		br_misp_retired.near_taken
	)
	local br_retired=br_inst_retired.near_taken
	if [[ ! -z $autofdo_all_branch_retired ]]; then
		for br in ${branches_retired[@]}
		do
			br_retired+=",$br"
		done
	fi

	perf record -b -e ${br_retired} -- ./gzip -k data.bin

	create_gcov \
		--binary=./gzip \
		--profile=perf.data \
		--gcov=${gcov_dir}/gzip.gcov \
		-gcov_version=1 >/dev/null

	configure_makefile
	make ${verbose:+V=1} clean

	make ${verbose:+V=1} \
		RT_CFLAGS="-fauto-profile=${gcov_dir}/gzip.gcov -Wno-suggest-attribute=cold" \
		RT_LDFLAGS=-fauto-profile=${gcov_dir}/gzip.gcov

	mv gzip gzip.afdo
}

fdo_test()
{
	gen_test_data

	local num=10
	echo -e "\n\tNAME\treal\tuser"
	for ((i = 0; i < ${num}; i++))
	do
		run_gzip orig gzip.orig
		run_gzip fdo gzip.fdo
		[[ -e gzip.afdo ]] && run_gzip autofdo gzip.afdo
		[[ -e gzip.bolt ]] && run_gzip bolt gzip.bolt
	done

	# Print results
	echo
	echo -e -n "NUM"
	echo -e -n "\tOrig"
	echo -e -n "\tFDO"
	[[ -e gzip.afdo ]] && echo -e -n "\tAutoFDO"
	[[ -e gzip.bolt ]] && echo -e -n "\tBOLT"
	echo
	for ((i = 0; i < ${num}; i++))
	do
		echo -e -n "${i}"
		echo -e -n "\t${orig_record[$i]}"
		echo -e -n "\t${fdo_record[$i]}"
		[[ -e gzip.afdo ]] && echo -e -n "\t${autofdo_record[$i]}"
		[[ -e gzip.bolt ]] && echo -e -n "\t${bolt_record[$i]}"
		echo
	done
}

while :;
do
	case $1 in
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		verbose=YES
		;;
	*)
		break
		;;
	esac
done

case $1 in
config)
	configure_makefile
	;;
compile-orig)
	compile_orig
	;;
compile-fdo)
	compile_fdo
	;;
compile-autofdo)
	shift
	compile_autofdo "$@"
	;;
test)
	fdo_test
	;;
clean)
	clean_git
	clean_gcov
	;;
*)
	cat<<-END

gzip-test.sh [-v|--verbose] [option]

config

compile-orig
compile-fdo
compile-autofdo [--br-all]

test

clean

END
	;;
esac

