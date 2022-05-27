#!/bin/bash
# Guest OS stress test
# Rong Tao <rongtao@cestc.cn>

OUTPUT_FILE=data.out
OUTPUT_FILE2=data2.out

###############################################################################
check_root()
{
	if [ $(id -G | awk '{print $1}') != 0 ]; then
		echo -e "\033[1;31mOnly root can do this.\033[m"
		exit 1
	fi
}

###############################################################################
# TEST dd
dd_output_()
{
	dd if=/dev/random of=$OUTPUT_FILE bs=1M count=100
}
dd_input_()
{
	test -f $OUTPUT_FILE && dd if=$OUTPUT_FILE of=$OUTPUT_FILE2 bs=1M count=100
}
dd_loop_()
{
	echo "Test dd, hit ctrl-c to end."
	while true
	do
		dd_output_ 2>/dev/null
		dd_input_ 2>/dev/null
	done
}

###############################################################################
mkdir_cd_rmdir_()
{
	dir=`mktemp -u /tmp/test____dirXXXXX`
	mkdir -p $dir
	cd $dir
	cd - >/dev/null
	rmdir $dir
}
neg_dentry_()
{
	# access no exist directory
	cd `mktemp -u /tmp/test____dirXXXXX` 2>/dev/null
}
dentry_loop_()
{
	echo "Test dentry, hit ctrl-c to end."
	while :
	do
		mkdir_cd_rmdir_
		neg_dentry_
	done
}

###############################################################################
numa_num=$(numactl --hardware | grep available | awk '{print $2}')

yes_for_each_numa_()
{
	test ! -f /usr/bin/numactl && echo "Install numactl first" && exit 1
	for ((i=0; i<$numa_num; i++))
	do
		numactl --cpunodebind=$i --membind=$i timeout 3 yes >/dev/null &
	done
}
yes_loop_()
{
	while :
	do
		yes_for_each_numa_
		sleep 2
	done
}

###############################################################################
iperf3_timeout=2
iperf3_()
{
	test ! -f /usr/bin/iperf3 && echo "Install iperf3 first" && exit 1
	NUMABIND_SERVER=""
	NUMABIND_CLIENT=""
	test $numa_num -gt 1 && NUMABIND_SERVER="numactl --cpunodebind=0 --membind=0"
	test $numa_num -gt 1 && NUMABIND_CLIENT="numactl --cpunodebind=1 --membind=1"
	$NUMABIND_SERVER timeout $iperf3_timeout iperf3 -s >/dev/null &
	sleep 0.05
	$NUMABIND_CLIENT timeout $iperf3_timeout iperf3 -c 0 >/dev/null
}

###############################################################################
memory_mount=/tmp/memory__mnt_dir
memory_block=block
memory_clean_()
{
	check_root
	while test -d $memory_mount
	do
		sudo umount $memory_mount
		rmdir $memory_mount
	done
}
malloc_()
{
	memory_clean_
	mkdir -p $memory_mount
	sudo mount -t tmpfs -o size=100M tmpfs $memory_mount
	# malloc(100M)
	dd if=/dev/random of=$memory_mount/$memory_block bs=1M count=99
}
free_()
{
	check_root
	rm $memory_mount/$memory_block
	sudo umount $memory_mount
	rmdir $memory_mount
}
malloc_free_()
{
	malloc_
	sleep 1
	free_
}
memory_loop_()
{
	echo "Test memory, hit ctrl-c to end."
	while :
	do
		malloc_
		free_
	done
}
##
###############################################################################
# Set all test here.
#
test_list=(\
	dd_input_ \
	dd_output_ \
	neg_dentry_ \
	mkdir_cd_rmdir_ \
	iperf3_ \
	yes_for_each_numa_ \
	malloc_free_ \
)
test_num=${#test_list[@]}

###############################################################################
# Record test
create_func_count()
{
	mkdir .test_count
}
clean_func_count()
{
	test -d .test_count && rm -rf .test_count
}
record_func_count()
{
	func=$1
	local cnt=0

	# Statistic function call count.
	test -f .test_count/$func && cnt=`cat .test_count/$func`
	cnt=$[ $cnt + 1 ]
	echo $cnt > .test_count/$func
}
print_func_count()
{
	# Print function count
	echo -e "\033[1;31m==== TEST COUNT ====\033[m"
	for func in $(ls .test_count)
	do
		echo -e "$func \t\t $(cat .test_count/$func)"
	done
}

###############################################################################
# TEST random
get_random_()
{
	echo `expr $RANDOM % $test_num`
}
random_loop_()
{
	check_root
	echo "Test all, hit ctrl-c to end."
	for ((i=0;i<$test_num;i++))
	do
		echo ${test_list[$i]}
	done

	while :
	do
		local idx=`get_random_`

		# TEST
		${test_list[$idx]} 2>/dev/null

		record_func_count ${test_list[$idx]}
	done
}

###############################################################################
signal_handler()
{
	echo "Catch SIG"
	rm -f $OUTPUT_FILE \
		$OUTPUT_FILE2
	rm -rf /tmp/test____dir*
	pkill iperf3
	pkill yes

	test -f .test_count/malloc_free_ && memory_clean_

	print_func_count
	clean_func_count
	exit 0
}

###############################################################################
# __usage__
usage()
{
cat<<'EOF'

usage guest-stress [OPT]

[OPT]
          dd	- Write/Read a file to/from disk.
      dentry	- Generate/Access/Remove dentry.
      iperf3	- Test Localhost iperf3 for 2 seconds.
         yes	- Exec 'yes' for 3 seconds in background on each numa node.
      memory	- Malloc/Free test with tmpfs.
         ALL	- Random test all above.

 All test is RUNNING FOREVER, hit ctrl-C to end.
EOF
	exit ${1-0}
}
logo_mark()
{
cat<<'EOF'

████████ ███████ ███████ ████████      ██████  ██    ██ ███████ ███████ ████████  ██████  ███████
   ██    ██      ██         ██        ██       ██    ██ ██      ██         ██    ██    ██ ██
   ██    █████   ███████    ██        ██   ███ ██    ██ █████   ███████    ██    ██    ██ ███████
   ██    ██           ██    ██        ██    ██ ██    ██ ██           ██    ██    ██    ██      ██
   ██    ███████ ███████    ██         ██████   ██████  ███████ ███████    ██     ██████  ███████

EOF
}

trap "echo Goodbye..." EXIT
trap "signal_handler" SIGINT

###############################################################################
# __main__

logo_mark

clean_func_count
create_func_count


case $1 in
dd)
	dd_loop_
	;;
dentry)
	dentry_loop_
	;;
iperf3)
	iperf3_
	;;
yes)
	yes_loop_
	;;
memory)
	memory_loop_
	;;
ALL)
	random_loop_
	;;
-h|--help|*)
	usage
	;;
esac
