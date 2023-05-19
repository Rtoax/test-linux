#!/bin/bash
# Test gzip/gunzip FDO
# git: https://git.savannah.gnu.org/git/gzip.git
#
# 2023-04-19	Rong Tao	Create this
# 2023-05-12	Rong Tao	Support autofdo
# 2023-05-15	Rong Tao	Support llvm-bolt
# 2023-05-19	Rong Tao	Auto compile original/fdo
#

set -e

verbose=

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
#  make clean
#  make CFLAGS=-fprofile-generate
#  ./gzip -k test.dat
#  make clean
#  make CFLAGS=-fprofile-use or
#  make CFLAGS="-fprofile-use -Wno-missing-profile -Wno-suggest-attribute=cold"
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
	if [[ ! -e test.dat ]]; then
		dd if=/dev/random of=${test_data} bs=4096 count=100000
	fi
}

clean_tmp()
{
	rm -fr \
		test.dat.gz
}

clean_exe()
{
	set -x
	rm -fr \
		gzip.orig \
		gzip.fdo \
		gzip.autofdo \
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
		-e gzip.autofdo
}

configure_makefile()
{
	clean_git
	make ${verbose:+V=1} clean || true

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

	./gzip -k test.dat

	configure_makefile
	make ${verbose:+V=1} clean

	make ${verbose:+V=1} RT_CFLAGS="-fprofile-use=${gcov_dir} -Wno-missing-profile -Wno-suggest-attribute=cold"

	mv gzip gzip.fdo
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
		[[ -e gzip.autofdo ]] && run_gzip autofdo gzip.autofdo
		[[ -e gzip.bolt ]] && run_gzip bolt gzip.bolt
	done

	# Print results
	echo
	echo -e -n "NUM"
	echo -e -n "\tOrig"
	echo -e -n "\tFDO"
	[[ -e gzip.autofdo ]] && echo -e -n "\tAutoFDO"
	[[ -e gzip.bolt ]] && echo -e -n "\tBOLT"
	echo
	for ((i = 0; i < ${num}; i++))
	do
		echo -e -n "${i}"
		echo -e -n "\t${orig_record[$i]}"
		echo -e -n "\t${fdo_record[$i]}"
		[[ -e gzip.autofdo ]] && echo -e -n "\t${autofdo_record[$i]}"
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
test)
	fdo_test
	;;
clean)
	clean_git
	clean_gcov
	;;
*)
	cat <<-EOF

	gzip-test.sh [-v|--verbose] [option]

	config

	compile-orig
	compile-fdo

	test

	clean

	EOF
	;;
esac

